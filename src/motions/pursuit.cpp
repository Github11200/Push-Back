#include "../../include/pursuit.h"
#include "../../include/chassis.h"
#include "../../include/utils.h"
#include <fstream>
#include <iostream>
#include <climits>

using namespace vex;
using namespace std;

Pursuit::Pursuit(Chassis *chassis, PursuitParams params)
{
  this->params = params;
  this->chassis = chassis;
}

Pursuit::~Pursuit()
{
  delete chassis;
}

int Pursuit::findClosestPoint()
{
  double minDistanceIndex = 0;
  double minDistance = INT_MAX;
  double distance = 0;
  Pose<double> robotPose = chassis->odometry->getPose();

  for (int i = 0; i < currentPath.size(); ++i)
  {
    distance = robotPose.position.distanceTo(currentPath[i].position);
    if (distance < minDistance)
    {
      minDistanceIndex = i;
      minDistance = distance;
    }
  }

  return minDistanceIndex;
}

double Pursuit::circleIntersect(Vector2D<double> point1, Vector2D<double> point2)
{
  Pose<double> robotPose = chassis->odometry->getPose();
  Vector2D<double> d = point2 - point1;
  Vector2D<double> f = point1 - robotPose.position;

  double a = d.dot(d);
  double b = 2 * f.dot(d);
  double c = f.dot(f) - params.lookAheadDistance * params.lookAheadDistance;
  double discriminant = b * b - 4 * a * c;

  // possible solution
  if (discriminant >= 0)
  {
    discriminant = sqrt(discriminant);

    double t1 = (-b - discriminant) / (2 * a);
    double t2 = (-b + discriminant) / (2 * a);

    if (t2 >= 0 && t2 <= 1)
      return t2;
    if (t1 >= 0 && t1 <= 1)
      return t1;
  }

  return -1;
}

Pose<double> Pursuit::findLookAheadPoint(Vector2D<double> lastLookAhead, int lastLookAheadIndex, int closestPointIndex)
{
  // Start as far down the path as possible
  int startIndex = max(closestPointIndex, lastLookAheadIndex);

  for (int i = startIndex; i < currentPath.size() - 1; ++i)
  {
    Vector2D<double> lastPoint = currentPath[i].position;
    Vector2D<double> currentPoint = currentPath[i + 1].position;

    double t = this->circleIntersect(lastPoint, currentPoint);

    if (t != -1)
    {
      Vector2D<double> lookAheadPoint = lerp<double>(lastPoint, currentPoint, t);
      return Pose<double>(lookAheadPoint);
    }
  }

  // No point found return last look ahead
  return Pose<double>(lastLookAhead);
}

// TODO: Make the full state feedback function go slower if the robot is off the path
double Pursuit::fullStateFeedback(Vector2D<double> target, double targetVelocity, double currentVelocity)
{
  Pose<double> robotPose = chassis->odometry->getPose();
  double positionError = robotPose.position.distanceTo(target);
  double velocityError = targetVelocity - currentVelocity;

  return (params.kP * positionError) + (params.kV * velocityError);
}

void Pursuit::followPath(Path path)
{
  currentPath = path;
  Pose<double> closestPoint;
  Pose<double> lookAheadPoint;
  Vector2D<double> lastLookAheadPoint = currentPath[0].position;
  int lastLookAheadPointIndex = 0;

  double curvature;
  double targetVelocity;
  double previousTargetVelocity = 0;
  double leftTargetVelocity;
  double rightTargetVelocity;

  // Used in the wait() function at the end of each loop iteration
  double waitTime = 20;

  timer pursuitTimer;
  pursuitTimer.clear();

  for (int i = 0; true; ++i)
  {
    // Check timeout
    if (pursuitTimer.time(timeUnits::msec) > params.timeout)
    {
      cout << "Pure Pursuit timed out" << endl;
      break;
    }

    // Get the closest point on the path
    int closestPointIndex = this->findClosestPoint();
    closestPoint = currentPath[closestPointIndex];

    // Check if we've reached a stop point (using orientation angle as speed storage)
    if (closestPoint.orientation.angle == 0)
    {
      cout << "Exiting Pure Pursuit curve" << endl;
      break;
    }

    // Get the point where the circle intersects
    lookAheadPoint = this->findLookAheadPoint(lastLookAheadPoint, lastLookAheadPointIndex, closestPointIndex);

    if (lookAheadPoint.position == lastLookAheadPoint)
    {
      wait(waitTime, vex::timeUnits::msec);
      continue;
    }

    // Get the curvature of the path
    Pose<double> curvaturePose = chassis->odometry->getPose();
    curvaturePose.orientation.angle = (M_PI / 2) - curvaturePose.orientation.constrainNegative180To180().toRad().angle;
    curvature = getSignedTangentArcCurvature(curvaturePose, lookAheadPoint.position);

    // Calculate the velocities
    targetVelocity = closestPoint.orientation.angle; // Speed stored in orientation angle
    targetVelocity = this->fullStateFeedback(lookAheadPoint.position, closestPoint.orientation.angle, previousTargetVelocity);

    // Apply slew rate limiting
    targetVelocity = slew<double>(targetVelocity, previousTargetVelocity, params.slewGain);

    // Calculate the target speeds for the motors (assuming trackWidth is available)
    double trackWidth = 12.75; // Default value, should be configured properly
    leftTargetVelocity = targetVelocity * (2 + curvature * trackWidth) / 2;
    rightTargetVelocity = targetVelocity * (2 - curvature * trackWidth) / 2;

    previousTargetVelocity = targetVelocity;

    // Normalize velocities if they exceed maximum
    double maxVel = max(fabs(leftTargetVelocity), fabs(rightTargetVelocity)) / 100;
    if (maxVel > 1)
    {
      leftTargetVelocity = maxVel;
      rightTargetVelocity = maxVel;
    }

    // Spin them in whatever direction based on whether you want to move forward or backward
    if (params.forward)
    {
      chassis->Left.spin(vex::directionType::fwd, leftTargetVelocity, vex::percentUnits::pct);
      chassis->Right.spin(vex::directionType::fwd, rightTargetVelocity, vex::percentUnits::pct);
    }
    else
    {
      chassis->Left.spin(vex::directionType::rev, leftTargetVelocity, vex::percentUnits::pct);
      chassis->Right.spin(vex::directionType::rev, rightTargetVelocity, vex::percentUnits::pct);
    }

    lastLookAheadPoint = lookAheadPoint.position;
    lastLookAheadPointIndex = closestPointIndex;

    wait(waitTime, vex::timeUnits::msec);
  }

  chassis->Left.stop(brake);
  chassis->Right.stop(brake);

  cout << "Exited Pure Pursuit Curve. Final Position:" << endl;
  Pose<double> finalPose = chassis->odometry->getPose();
  cout << finalPose.position.x << ", " << finalPose.position.y << endl;
}