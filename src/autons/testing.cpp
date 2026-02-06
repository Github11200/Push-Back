#include "autons.h"
#include "vex.h"
#include "types/params.h"

using namespace vex;
using namespace std;

void Autons::testing()
{
  chassisReference->odometry->setPosition(-46.5, 16.5, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  chassisReference->driveDistance(3, chassisReference->getAbsoluteHeading().angle, {}, turnParams10_deg(), {});
}