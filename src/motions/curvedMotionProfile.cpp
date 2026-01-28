// #include "chassis.h"

// using namespace std;
// using namespace vex;

// struct TrajectoryParams
// {
//   CurvedMotionProfile profile;
//   double trackWidth;
// };

// double constrainVelocity(TrajectoryParams params, double t)
// {
//   // Velocity due to curvature
//   double radius = 1 / params.profile.curve.getCurvature(t);
//   double velocityDueToCurvature = params.profile.maximumVelocity * (radius / (radius + (params.trackWidth / 2)));

//   // Maximum attainable velocity
//   double maximumAttainableVelocity = sqrt() return 0;
// }

// vector<MotionProfilePose<double>> generateTrajectory(TrajectoryParams params)
// {
//   double accumulatedTime = 0;

//   CubicBezier curve = params.profile.curve;
//   vector<MotionProfilePose<double>> trajectory;
//   MotionProfilePose<double> previousPose(0, curve.getPosition(0).x, curve.getPosition(0).y, atan2(curve.getFirstDerivative(0).y, curve.getFirstDerivative(0).x), 0, 0, 0);

//   while (t < 1)
//   {

//     accumulatedTime += params.profile.dt;
//   }

//   return trajectory;
// }

// void Chassis::curvedMotionProfile(CurvedMotionProfile profile)
// {
//   vector<MotionProfilePose<double>> trajectory = generateTrajectory({.profile = profile, .trackWidth = trackWidth});
// }