#include "chassis.h"

using namespace std;
using namespace vex;

vector<MotionProfilePose<double>> generateTrajectory(CurvedMotionProfile &profile, double trackWidth)
{
  double t = 0;
  double d = 0;

  CubicBezier curve = profile.curve;
  vector<MotionProfilePose<double>> trajectory;
  MotionProfilePose<double> previousPose(curve.getPosition(0).x, curve.getPosition(0).y, atan2(curve.getFirstDerivative(0).y, curve.getFirstDerivative(0).x), 0, 0);

  while (t < 1)
  {
    Vector2D<double> position = curve.getPosition(t);
    Vector2D<double> velocity = curve.getFirstDerivative(t);
    Vector2D<double> acceleration = curve.getSecondDerivative(t);

    double curvature = curve.getCurvature(t);
    double maxVelocityDueToCurvature = (2 * profile.maximumVelocity) / (2 + trackWidth * curvature);

    double dt = d / hypot(velocity.x, velocity.y);

    t += dt;
  }

  return trajectory;
}

void Chassis::curvedMotionProfile(CurvedMotionProfile profile)
{
  vector<MotionProfilePose<double>> trajectory = generateTrajectory(profile, trackWidth);
}