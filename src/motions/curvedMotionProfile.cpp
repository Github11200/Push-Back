#include "chassis.h"
#include "types/motionProfilePose.h"

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

    double constrainedSpeed = limitSpeedDueToCurvature(speed, curvature);
    double acceleration = curve.getSecondDerivative(t).magnitude();

    distances.push_back(currentDistance);
    velocities.push_back(constrainedSpeed);
    accelerations.push_back(acceleration);
  }

  vector<double> leftPass = pass(distances, velocities, accelerations);

  reverse(distances.begin(), distances.end());
  reverse(velocities.begin(), velocities.end());
  reverse(accelerations.begin(), accelerations.end());

  // Right --> Left pass
  vector<double> rightPass = pass(distances, velocities, accelerations);

  reverse(distances.begin(), distances.end());
  reverse(velocities.begin(), velocities.end());
  reverse(accelerations.begin(), accelerations.end());

  for (int i = 0; i < leftPass.size(); ++i)
    velocities[i] = min(leftPass[i], rightPass[i]);

  vector<double> times({0.0});

  // Distances --> Times
  for (int i = 1; i < velocities.size(); ++i)
  {
    double time = 0;

    double deltaD = distances[i] - distances[i - 1];
    double acceleration = (pow(velocities[i], 2) - pow(velocities[i - 1], 2)) / (2 * deltaD);

    if (acceleration == 0.0)
      time = deltaD / velocities[i];
    else
      time = (velocities[i] - velocities[i - 1]) / acceleration;

    times.push_back(time);
  }

  vector<MotionProfilePose> trajectory;
  for (int i = 0; i < times.size(); ++i)
    trajectory.push_back(MotionProfilePose<double>(times[i], velocities[i], accelerations[i]));

  return trajectory;
}

void Chassis::curvedMotionProfile(CurvedMotionProfile profile)
{
  vector<MotionProfilePose<double>> trajectory = generateTrajectory({.profile = profile, .trackWidth = trackWidth});
}