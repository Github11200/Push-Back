#ifndef CHASSIS_H
#define CHASSIS_H

#include "odometry/odometry.h"
#include "pid/pid.h"
#include "pursuit.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include "utils/bezier.h"

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
  Odometry *odometry;
  // Pursuit *pursuit;

  // TODO: Struct for properties
  Chassis(double inertialScaling,
          TrackerSetup trackerSetup,
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

  void driveDistance(double distance, double heading, DriveParams driveParams, TurnParams turnParams, Settings settings);
  void driveToPoint(const Pose<double> &target, DriveParams driveParams, TurnParams turnParams, Settings settings);
  void driveToPose(const Pose<double> &target, DriveParams driveParams, TurnParams turnParams, Settings settings, double lead = 0, double setback = 0, double driveCompensation = 0);
  void turnTo(const Pose<double> &target, TurnParams params, Settings settings);
  void curvedMotionProfile(CurvedMotionProfile profile);

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