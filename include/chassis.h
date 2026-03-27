#ifndef CHASSIS_H
#define CHASSIS_H

#include "odometry/odometry.h"
#include "controlSystems/pid.h"
#include "pursuit.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include "utils/bezier.h"
#include "config.h"

#include <stdlib.h>
#include <complex>
#include <iostream>
#include <algorithm>

using namespace vex;
using namespace std;

enum SwingDirection
{
  SWING_LEFT,
  SWING_RIGHT,
  NONE
};

struct DriveToPointParams
{
  Pose<double> target;
  DriveParams driveParams;
  TurnParams turnParams;
  Settings settings;
};

class Chassis
{
private:
  double inertialScaling = 360;
  double trackWidth;
  Pose<double> target;
  DriveToPointParams driveToPointParams;
  bool driveToPointRunning = false;
  bool cancelDriveToPoint = false;

public:
  double forwardTrackerInchesToDegreesRatio;
  double sidewaysTrackerInchesToDegreesRatio;
  Odometry *odometry;

  Chassis();
  ~Chassis();

  void driveDistance(double distance, double heading, DriveParams driveParams, TurnParams turnParams, Settings settings);
  void driveWithVoltage(double power, double timeout, double heading, TurnParams turnParams, Settings settings);
  void driveToPoint(Pose<double> target, DriveParams driveParams, TurnParams turnParams, Settings settings, bool useClassTargetVariable = false);
  void driveToPose(const Pose<double> &target, DriveParams driveParams, TurnParams turnParams, Settings settings, double lead = 0, double setback = 0, double driveCompensation = 0);
  void turnTo(const Pose<double> &target, TurnParams params, Settings settings, SwingDirection swing = NONE);
  void curvedMotionProfile(CurvedMotionProfile profile, RamseteParams ramseteParams);

  // false = left, and true = right
  void driveWithTwoDistanceSensors(double targetYDistance, double targetXDistance, DriveParams driveParams, TurnParams turnParams, Settings settings, bool leftOrRightSensor);

  void trapezoidalMotionProfile(double distance, MotionProfile motionProfileSettings, DriveParams driveParams, TurnParams turnParams, Settings settings);

  Angle<double> getAbsoluteHeading();
  Pair getMotorsPosition();

  void calibrateInertial();
  void resetEncoders();

  double getForwardTrackerPosition();
  double getSidewaysTrackerPosition();
};

#endif