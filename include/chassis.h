#ifndef CHASSIS_H
#define CHASSIS_H

#include "v5.h"
#include "v5_vcs.h"

#include "odometry/odometry.h"
#include "types/pose.h"
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
  motor_group Left, Right;

public:
  Chassis(/* args */);

  void driveDistance(double distance, DriveParams driveParams, TurnParams turnParams, Settings settings);
  void driveToPoint(Pose<double> target, DriveParams driveParams, TurnParams turnParams, Settings settings);
  void driveToPose(Pose<double> target, DriveParams driveParams, TurnParams turnParams, Settings settings, double lead);

  void turnTo(Pose<double> target, TurnParams params, Settings settings);

  Angle<double> getAbsoluteHeading();
  pair<double, double> getMotorVelocities(double driveOutput, double turnOutput);

  ~Chassis();
};

#endif