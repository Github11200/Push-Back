#include "chassis.h"

using namespace std;
using namespace vex;

Pair getVelocities(MotionProfilePose<double> currentPoint, double trackWidth)
{
  return Pair(0, 0);
}

vector<MotionProfilePose<double>> generateTrajectory(CurvedMotionProfile &profile, double trackWidth)
{
  double t = 0;

  CubicBezier curve = profile.curve;
  vector<MotionProfilePose<double>> trajectory;
  MotionProfilePose<double> previousPose(curve.getPosition(0).x, curve.getPosition(0).y, atan2(curve.getFirstDerivative(0).y, curve.getFirstDerivative(0).x), 0, 0, 0);

  while (t < 1)
  {
    Vector2D<double> position = curve.getPosition(t);
    Vector2D<double> velocity = curve.getFirstDerivative(t);
    Vector2D<double> acceleration = curve.getSecondDerivative(t);

    double curvature = curve.getCurvature(t);
    double maxVelocityDueToCurvature = (2 * profile.maximumVelocity) / (2 + trackWidth * fabs(curvature));
    double maxVelocityDueToPrevious = sqrt(previousPose.velocity * previousPose.velocity + 2 * profile.maximumAcceleration * profile.pointsDisplacement);

    double maxVelocity = min(min(maxVelocityDueToCurvature, maxVelocityDueToPrevious), profile.maximumVelocity);

    MotionProfilePose<double> currentPose(position.x, position.y, atan2(velocity.y, velocity.x), maxVelocity, maxVelocity * curvature, curvature);
    trajectory.push_back(currentPose);
    previousPose = currentPose;
    double dt = profile.pointsDisplacement / hypot(velocity.x, velocity.y);

    t += dt;
  }

  t = 1;
  previousPose = MotionProfilePose<double>(curve.getPosition(1).x, curve.getPosition(1).y, 0, 0, 0);
  int i = trajectory.size() - 1;
  while (t > 0)
  {
    trajectory[i] = trajectory[i].velocity > previousPose.velocity ? previousPose : trajectory[i];

    Vector2D<double> position = curve.getPosition(t);
    Vector2D<double> velocity = curve.getFirstDerivative(t);
    Vector2D<double> acceleration = curve.getSecondDerivative(t);

    double curvature = curve.getCurvature(t);
    double maxVelocityDueToCurvature = (2 * profile.maximumVelocity) / (2 + trackWidth * fabs(curvature));
    double maxVelocityDueToPrevious = sqrt(previousPose.velocity * previousPose.velocity + 2 * profile.maximumAcceleration * profile.pointsDisplacement);

    double maxVelocity = min(min(maxVelocityDueToCurvature, maxVelocityDueToPrevious), profile.maximumVelocity);

    previousPose = MotionProfilePose<double>(position.x, position.y, atan2(velocity.y, velocity.x), maxVelocity, maxVelocity * curvature, curvature);

    double dt = profile.pointsDisplacement / hypot(velocity.x, velocity.y);
    t -= dt;
    --i;
  }

  return trajectory;
}

void Chassis::curvedMotionProfile(CurvedMotionProfile profile)
{
  vector<MotionProfilePose<double>> trajectory = generateTrajectory(profile, trackWidth);
}