#include "autons.h"
#include "vex.h"
#include "types/params.h"

using namespace vex;
using namespace std;

void Autons::testing()
{
  DriveParams temp = driveParams20_in();
  chassisReference->odometry->startPositionTrackThread(true);

  temp.driveSlew = 12;
  temp.driveMinVoltage = 10;
  temp.driveSettleError = 2;
  chassisReference->driveToPoint(Pose<double>(0, 20, 0), temp, turnParams10_deg(), {});
  chassisReference->driveToPoint(Pose<double>(50, 50, 0), driveParams10_in(), turnParams10_deg(), {});
  chassisReference->driveToPoint(Pose<double>(0, 10, 0), temp, turnParams10_deg(), {});
  // chassisReference->driveDistance(10, 0, temp, turnParams10_deg(), {.forwards = false});
}