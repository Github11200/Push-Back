#include "chassis.h"
#include "types/motionProfilePose.h"

using namespace std;
using namespace vex;

struct TrajectoryParams
{
  CurvedMotionProfile profile;
  double trackWidth;
};

double limitSpeedDueToCurvature(double speed, double curvature, double trackWidth)
{
  double radius = 1 / curvature;
  return speed * (radius / (radius + (trackWidth / 2)));
}

vector<double> pass(const vector<double> &distances, const vector<double> &velocities, const vector<double> &accelerations)
{
  vector<double> constrainedVelocities;
  constrainedVelocities.push_back(velocities[0]);

  int length = distances.size();
  for (int i = 1; i < length; ++i)
  {
    double deltaD = distances[i] - distances[i - 1];
    double maxAttainableVelocity = sqrt(pow(velocities[i - 1], 2) + 2 * accelerations[i] * deltaD);

    constrainedVelocities.push_back(min(velocities[i], maxAttainableVelocity));
  }

  return constrainedVelocities;
}

vector<MotionProfilePose<double>> generateTrajectory(TrajectoryParams params)
{
  CubicBezier curve = params.profile.curve;

  vector<Vector2D<double>> positions;
  vector<double> curvatures;
  vector<double> distances;
  vector<double> velocities;
  vector<double> accelerations;

  // First constrain based on only the curvature
  int numberOfSegments = curve.getArcLength(1) / params.profile.distanceBetweenPoints;
  for (int i = 0; i < numberOfSegments; ++i)
  {
    double t = static_cast<double>(i) / static_cast<double>(numberOfSegments);

    double currentDistance = curve.getArcLength(t);

    double speed = curve.getFirstDerivative(t).magnitude();
    double curvature = curve.getCurvature(t);

    double constrainedSpeed = limitSpeedDueToCurvature(speed, curvature, params.trackWidth);
    double acceleration = curve.getSecondDerivative(t).magnitude();

    positions.push_back(curve.getPosition(t));
    curvatures.push_back(curvature);
    distances.push_back(currentDistance);
    velocities.push_back(constrainedSpeed);
    accelerations.push_back(acceleration);
  }

  vector<double> leftPass = pass(distances, velocities, accelerations);

  std::reverse(distances.begin(), distances.end());
  std::reverse(velocities.begin(), velocities.end());
  std::reverse(accelerations.begin(), accelerations.end());

  // Right --> Left pass
  vector<double> rightPass = pass(distances, velocities, accelerations);

  std::reverse(distances.begin(), distances.end());
  std::reverse(velocities.begin(), velocities.end());
  std::reverse(accelerations.begin(), accelerations.end());

  for (int i = 0; i < leftPass.size(); ++i)
    velocities[i] = min(leftPass[i], rightPass[i]);

  vector<double> times({0.0});

  // Distances --> Times
  double time = 0;
  for (int i = 1; i < velocities.size(); ++i)
  {
    double deltaD = distances[i] - distances[i - 1];
    double acceleration = (pow(velocities[i], 2) - pow(velocities[i - 1], 2)) / (2 * deltaD);

    if (acceleration == 0.0)
      time += deltaD / velocities[i];
    else
      time += (velocities[i] - velocities[i - 1]) / acceleration;

    times.push_back(time);
  }

  vector<MotionProfilePose<double>> trajectory;
  for (int i = 0; i < times.size(); ++i)
    trajectory.push_back(MotionProfilePose<double>(times[i],
                                                   Pose<double>(positions[i],
                                                                atan2(positions[i].y, positions[i].x)),
                                                   velocities[i],
                                                   curvatures[i] * velocities[i],
                                                   accelerations[i]));

  return trajectory;
}

void Chassis::curvedMotionProfile(CurvedMotionProfile profile, RamseteParams ramseteParams, double kv)
{
  vector<MotionProfilePose<double>> trajectory = generateTrajectory({.profile = profile, .trackWidth = trackWidth});

  for (MotionProfilePose<double> profilePose : trajectory)
  {
    cout << "Time: " << profilePose.time << endl
         << "X: " << profilePose.pose.position.x << endl
         << "Y: " << profilePose.pose.position.y << endl
         << "Angle: " << profilePose.pose.orientation.angle << endl
         << "Velocity: " << profilePose.velocity << endl
         << "Angular Velocity: " << profilePose.angularVelocity << endl
         << "Acceleration: " << profilePose.acceleration << endl;

    cout << "====================================" << endl;
  }

  return;

  for (int i = 0; i < trajectory.size(); ++i)
  {
    double desiredVelocity = trajectory[i].velocity;
    double desiredAngularVelocity = trajectory[i].angularVelocity;

    Pose<double> desiredPose = trajectory[i].pose;
    Pose<double> currentPose = odometry->getPose();
    Angle<double> currentAngle = getAbsoluteHeading().constrainNegative180To180();

    double xError = desiredPose.position.x - currentPose.position.x;
    double yError = desiredPose.position.y - currentPose.position.y;
    double angleError = (desiredPose.orientation - currentPose.orientation).constrainNegative180To180().angle;

    double transformationMatrix[3][3] = {{cos(currentAngle.toRad().angle), sin(currentAngle.toRad().angle), 0},
                                         {-sin(currentAngle.toRad().angle), cos(currentAngle.toRad().angle), 0},
                                         {0, 0, 1}};

    double localXError = xError * transformationMatrix[0][0] + yError * transformationMatrix[0][1] + angleError * transformationMatrix[0][2];
    double localYError = xError * transformationMatrix[1][0] + yError * transformationMatrix[1][1] + angleError * transformationMatrix[1][2];
    double localAngleError = xError * transformationMatrix[2][0] + yError * transformationMatrix[2][1] + angleError * transformationMatrix[2][2];

    double gainValue = 2 * ramseteParams.zeta * sqrt(pow(desiredAngularVelocity, 2) + ramseteParams.beta * pow(desiredVelocity, 2));

    double linearVelocity = (desiredVelocity * cos(localAngleError) + gainValue * localXError) / (3.25 * M_PI);
    double angularVelocity = desiredAngularVelocity + gainValue * localAngleError + ((ramseteParams.beta * desiredVelocity * sin(localAngleError) * localYError) / localAngleError);

    double leftPower = (linearVelocity + angularVelocity) * kv;
    double rightPower = (linearVelocity - angularVelocity) * kv;

    Left.spin(vex::directionType::fwd, leftPower, vex::voltageUnits::volt);
    Right.spin(vex::directionType::fwd, rightPower, vex::voltageUnits::volt);

    if (i != trajectory.size() - 1)
      wait(trajectory[i + 1].time - trajectory[i].time);
  }

  Left.stop(coast);
  Right.stop(coast);
}