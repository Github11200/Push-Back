#include "autons.h"
#include "vex.h"
#include "types/params.h"

using namespace vex;
using namespace std;

void Autons::testing()
{
  chassisReference->driveDistance(10, chassisReference->getAbsoluteHeading(), {}, {}, {});
}