#include "autons.h"
#include "vex.h"
#include "types/params.h"

using namespace vex;
using namespace std;

void Autons::testing()
{
  DriveParams driveParams;
  TurnParams turnParams;

  chassisReference->odometry->setPosition(-46.5, 16.5, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  chassisReference->driveDistance(5, chassisReference->getAbsoluteHeading().angle, driveParams5_in(), turnParams10_deg(), {});
}