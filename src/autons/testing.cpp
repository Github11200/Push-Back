#include "autons.h"
#include "vex.h"
#include "types/params.h"

using namespace vex;
using namespace std;

void Autons::testing()
{
  DriveParams temp = driveParams20_in();
  chassisReference->odometry->startPositionTrackThread(false);
  chassisReference->driveToPoint(Pose<double>(0, 10, 0), temp, turnParams10_deg(), {});
  chassisReference->driveDistance(10, 0, temp, turnParams10_deg(), {.forwards = false});
}