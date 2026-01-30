#include "chassis.h"

using namespace std;
using namespace vex;

/*

- Generate trajectory for (distance, velocity)
- For calculating the distance, find t by dividing by the number of segments in the
path by where you are right now, i
- Limit the speed as you go along from curvature, the max velocity in the profile
and the max speed you can attain.
- Now do a left pass after the right pass
- Convert the (distance, velocity) to a (time, velocity) graph by using kinematics
equations, and also check for the acceleration.

*/

struct TrajectoryParams
{
  CurvedMotionProfile profile;
  double trackWidth;
};

double constrainVelocity(TrajectoryParams params, double t)
{
  // Velocity due to curvature
  double radius = 1 / params.profile.curve.getCurvature(t);
  double velocityDueToCurvature = params.profile.maximumVelocity * (radius / (radius + (params.trackWidth / 2)));

  // Maximum attainable velocity
  double maximumAttainableVelocity = sqrt(0);
  return min(params.profile.maximumVelocity, min(velocityDueToCurvature, maximumAttainableVelocity));
}

void pass(vector<MotionProfilePose<double>> &trajectory)
{
}

vector<MotionProfilePose<double>> generateTrajectory(TrajectoryParams params)
{
  double accumulatedDistance = 0;

  CubicBezier curve = params.profile.curve;
  vector<MotionProfilePose<double>> trajectory;
  MotionProfilePose<double> previousPose(0, curve.getPosition(0).x, curve.getPosition(0).y, atan2(curve.getFirstDerivative(0).y, curve.getFirstDerivative(0).x), 0, 0, 0);

  double numberOfSegments = curve.getArcLength() / params.profile.distanceBetweenPoints;
  for (int i = 0; i < numberOfSegments; ++i)
  {
    double t = numberOfSegments / static_cast<double>(i);

    Vector2D<double> currentPosition = curve.getPosition(t);

    double velocity = curve.getFirstDerivative(t).magnitude();
    double acceleration = curve.getSecondDerivative(t).magnitude();
    double curvature = curve.getCurvature(t);
    double angle = atan2(currentPosition.y, currentPosition.x);

    double constrainedVelocity = constrainVelocity(params, t);

    trajectory.push_back(MotionProfilePose<double>(0,
                                                   currentPosition.x,
                                                   currentPosition.y,
                                                   angle,
                                                   velocity,
                                                   acceleration,
                                                   curvature));
  }

  return trajectory;
}

void Chassis::curvedMotionProfile(CurvedMotionProfile profile)
{
  vector<MotionProfilePose<double>> trajectory = generateTrajectory({.profile = profile, .trackWidth = trackWidth});
}