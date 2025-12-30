#include "autons.h"
#include "vex.h"
#include "types/params.h"

using namespace vex;
using namespace std;

void Autons::testing()
{
  DriveParams temp = driveParams20_in();
  temp.driveKp = 0.7;
  chassisReference->odometry->setPosition(-46.5, 16.5, 90);
  chassisReference->driveToPose(Pose<double>(-15, 31, 45), temp, turnParams30_deg(), {}, 0.575, 0, 0);
}