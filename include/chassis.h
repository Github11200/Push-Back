#ifndef CHASSIS_H
#define CHASSIS_H

#include "odometry/odometry.h"
#include "pid/pid.h"
#include "pursuit.h"
#include "utils/timer.h"
#include "utils/logger.h"
#include "utils/utils.h"

#include <stdlib.h>
#include <complex>
#include <iostream>

using namespace vex;
using namespace std;

class Chassis
{
private:
  rotation forwardTracker;
  rotation sidewaysTracker;

  double inertialScaling = 360;
  double trackWidth;
  double inchesToDegreesRatio;

public:
  Odometry *odometry;
  Pursuit *pursuit;
  inertial Inertial;

  Chassis(
      int inertialPort,
      TrackerSetup trackerSetup,
      int forwardTrackerPort,
      int sidewaysTrackerPort,
      double inchesToDegreesRatio,
      double forwardTrackerDistance,
      double sidewaysTrackerDistance,
      double frontDistanceSensorDistance,
      double leftDistanceSensorDistance,
      double rightDistanceSensorDistance,
      bool enableLogs = false);
  ~Chassis();

  void driveDistance(double distance, DriveParams driveParams, TurnParams turnParams, Settings settings);
  void driveToPoint(Pose<double> target, DriveParams driveParams, TurnParams turnParams, Settings settings);
  void driveToPose(Pose<double> target, DriveParams driveParams, TurnParams turnParams, Settings settings, double lead, double setback, double driveCompensation);
  void turnTo(Pose<double> target, TurnParams params, Settings settings);

  void followPath(vector<Pose<double>> path, PursuitParams params);

  void trapezoidalMotionProfile(double distance, MotionProfile motionProfileSettings, DriveParams driveParams, TurnParams turnParams, Settings settings);

  Angle<double>
  getAbsoluteHeading();
  Pair getMotorsPosition();

  void calibrateInertial();
  void resetEncoders();

  double getForwardTrackerPosition();
  double getSidewaysTrackerPosition();
};

#endif