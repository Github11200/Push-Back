#include "autons.h"
#include "vex.h"
#include "types/params.h"

using namespace vex;
using namespace std;

void Autons::testing()
{
  chassisReference->odometry->setPosition(11, -11, 135);
  chassisReference->odometry->startPositionTrackThread(false);

  // chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::RIGHT);
  // cout << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;

  CurvedMotionProfile motionProfile;
  Vector2D<double> points[4] = {
      Vector2D<double>(11, -11), Vector2D<double>(47, -47),
      Vector2D<double>(47, 47), Vector2D<double>(13, 13)};
  motionProfile.curve = CubicBezier(points);
  motionProfile.distanceBetweenPoints = 0.25;
  motionProfile.initialVelocity = 10;
  motionProfile.finalVelocity = 0;
  motionProfile.maximumAcceleration = 15;
  motionProfile.maximumVelocity = 50;
  motionProfile.kV = 0.005;
  motionProfile.kA = 0.03;

  RamseteParams params;
  params.beta = 45;
  params.zeta = 0.4;
  chassisReference->curvedMotionProfile(motionProfile, params);

  // chassisReference->driveToPose(Pose<double>(-20, -20, 0), {.driveSettleTime = 2000}, {.turnSettleTime = 2000}, {}, 0.8, 0.8);
}