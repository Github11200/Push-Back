#include "autons.h"
#include "vex.h"
#include "types/params.h"

using namespace vex;
using namespace std;

void Autons::testing()
{
  chassisReference->odometry->setPosition(0, 0, 0);
  chassisReference->odometry->startPositionTrackThread(false);

  // TurnParams params = turnParams45_deg();
  // DriveParams driveParams = driveParams50_in();
  // driveParams.driveTimeout = 10000;
  // driveParams.driveSettleError = 0.5;
  // params.turnSettleError = 0.5;
  // params.turnTimeout = 10000;
  // chassisReference->driveToPose(Pose<double>(-47, 47, 270), driveParams, params, {}, 0.5, 0, 2.5);
  chassisReference->turnTo(Pose<double>(0, 0, 90), {}, {}, SwingDirection::SWING_RIGHT);
}