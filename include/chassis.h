#ifndef CHASSIS_H
#define CHASSIS_H

#include "v5.h"
#include "v5_vcs.h"

#include "odometry/odometry.h"
#include "types/pose.h"
#include "types/angle.h"
#include "types/params.h"

#include "pid/pid.h"
#include "utils.h"

#include <stdlib.h>
#include <complex>

using namespace vex;
using namespace std;

class Chassis
{
private:
  inertial Inertial;
  double inertialScaling = 360;

public:
  Chassis(/* args */);

  void driveDistance(double distance, DriveParams driveParams, TurnParams turnParams, Settings settings);
  void driveToPoint(Pose<double> target, DriveParams driveParams, TurnParams turnParams, Settings settings);
  void driveToPose(Pose<double> target, DriveParams driveParams, TurnParams turnParams, Settings settings, double lead);

  void turnToAngle(Angle<double> target, TurnParams params, Settings settings);
  void turnToPoint(Pose<double> target, TurnParams params, Settings settings);

  Angle<double> getAbsoluteHeading();

  ~Chassis();
};

#endif