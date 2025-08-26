#ifndef CHASSIS_H
#define CHASSIS_H

#include "odometry/odometry.h"
#include "pid/pid.h"
#include "pursuit.h"
#include "timer.h"
#include "logger.h"

#include <stdlib.h>
#include <complex>

using namespace vex;
using namespace std;

struct Pair
{
  double left;
  double right;
  Pair(double left, double right) : left(left), right(right) {}
};

class Chassis
{
private:
  inertial Inertial;
  rotation forwardTracker;
  rotation sidewaysTracker;

  double inertialScaling = 360;
  double trackWidth;
  double inchesToDegreesRatio;

public:
  Odometry *odometry;
  Pursuit *pursuit;
  motor_group Left, Right;

  Chassis(int inertialPort,
          int forwardTrackerPort,
          int sidewaysTrackerPort,
          motor_group leftMotorGroup,
          motor_group rightMotorGroup,
          double inchesToDegreesRatio,
          double forwardTrackerDistance,
          double sidewaysTrackerDistance);
  ~Chassis();

  void driveDistance(double distance, DriveParams driveParams, TurnParams turnParams, Settings settings);
  void driveToPoint(Pose<double> target, DriveParams driveParams, TurnParams turnParams, Settings settings);
  void driveToPose(Pose<double> target, DriveParams driveParams, TurnParams turnParams, Settings settings, double lead, double setback, double driveCompensation);
  void turnTo(Pose<double> target, TurnParams params, Settings settings);

  void followPath(vector<Pose<double>> path, PursuitParams params);

  Angle<double> getAbsoluteHeading();
  Pair getMotorVelocities(double driveOutput, double turnOutput);
  Pair getMotorsPosition();

  void calibrateInertial();
  void resetEncoders();

  double getForwardTrackerPosition();
  double getSidewaysTrackerPosition();
};

#endif