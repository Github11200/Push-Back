#include "autons.h"
#include "vex.h"
#include "types/params.h"

using namespace vex;
using namespace std;

void Autons::testing()
{
  DriveParams driveParams;
  TurnParams turnParams;

  chassisReference->odometry->setPosition(0, 0, 0);
  chassisReference->odometry->startPositionTrackThread(false);
}