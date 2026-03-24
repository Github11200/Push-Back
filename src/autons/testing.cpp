#include "autons.h"
#include "vex.h"
#include "types/params.h"

using namespace vex;
using namespace std;

void Autons::testing()
{
  chassisReference->odometry->setPosition(0, 0, 0);
  chassisReference->odometry->startPositionTrackThread(false);

  CurvedMotionProfile motionProfile;
  Vector2D<double> points[4] = {
      Vector2D<double>(0, 0), Vector2D<double>(0, 0),
      Vector2D<double>(0, 10), Vector2D<double>(0, 10)};
  motionProfile.curve = CubicBezier(points);
  motionProfile.distanceBetweenPoints = 0.25;
  motionProfile.initialVelocity = 0;
  motionProfile.finalVelocity = 0;
  motionProfile.kA = 2;
  motionProfile.maximumAcceleration = 4;
  motionProfile.maximumVelocity = 50;

  RamseteParams params;
  params.beta = 5;
  params.zeta = 0.1;

  chassisReference->curvedMotionProfile(motionProfile, params, 1.2);
}