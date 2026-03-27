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
      Vector2D<double>(0, 0), Vector2D<double>(0, 15),
      Vector2D<double>(0, 15), Vector2D<double>(-20, 20)};
  motionProfile.curve = CubicBezier(points);
  motionProfile.distanceBetweenPoints = 0.25;
  motionProfile.initialVelocity = 0;
  motionProfile.finalVelocity = 0;
  motionProfile.maximumAcceleration = 15;
  motionProfile.maximumVelocity = 50;
  motionProfile.kV = 0.005;
  motionProfile.kA = 0.03;

  RamseteParams params;
  params.beta = 45;
  params.zeta = 0.4;

  chassisReference->curvedMotionProfile(motionProfile, params);
}