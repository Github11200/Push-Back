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
  double inertialScaling = 360;
  double trackWidth;

public:
  double forwardTrackerInchesToDegreesRatio;
  double sidewaysTrackerInchesToDegreesRatio;
  rotation forwardTracker;
  rotation sidewaysTracker;
  Odometry *odometry;
  // Pursuit *pursuit;
  inertial Inertial;

  Chassis(
      int inertialPort,
      double inertialScaling,
      TrackerSetup trackerSetup,
      int forwardTrackerPort,
      int sidewaysTrackerPort,
      double forwardTrackerInchesToDegreesRatio,
      double sidewaysTrackerInchesToDegreesRatio,
      double forwardTrackerDistance,
      double sidewaysTrackerDistance,
      double frontDistanceSensorDistance,
      double leftDistanceSensorDistance,
      double rightDistanceSensorDistance,
      double backDistanceSensorDistance,
      bool enableLogs = false);
  ~Chassis();

  void driveDistance(double distance, double heading, DriveParams driveParams = DriveParams(), TurnParams turnParams = TurnParams(), Settings settings = Settings());
  void driveToPoint(Pose<double> target, DriveParams driveParams = DriveParams(), TurnParams turnParams = TurnParams(), Settings settings = Settings());
  void driveToPose(Pose<double> target, DriveParams driveParams = DriveParams(), TurnParams turnParams = TurnParams(), Settings settings = Settings(), double lead = 0, double setback = 0, double driveCompensation = 0.1);
  void turnTo(Pose<double> target, TurnParams params, Settings settings);

  // void followPath(vector<Pose<double>> path, PursuitParams params);

  void trapezoidalMotionProfile(double distance, MotionProfile motionProfileSettings, DriveParams driveParams, TurnParams turnParams, Settings settings);

  Angle<double> getAbsoluteHeading();
  Pair getMotorsPosition();

  void calibrateInertial();
  void resetEncoders();

  double getForwardTrackerPosition();
  double getSidewaysTrackerPosition();
};

#endif