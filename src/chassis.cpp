#include "../include/chassis.h"

using namespace vex;
using namespace std;

// TODO: Update the ports for all the sensors
Chassis::Chassis(int inertialPort,
                 int forwardTrackerPort,
                 int sidewaysTrackerPort,
                 motor_group leftMotorGroup,
                 motor_group rightMotorGroup,
                 double inchesToDegreesRatio,
                 double forwardTrackerDistance,
                 double sidewaysTrackerDistance) : Inertial(inertialPort),
                                                   forwardTracker(forwardTrackerPort),
                                                   sidewaysTracker(sidewaysTrackerPort),
                                                   Left(leftMotorGroup),
                                                   Right(rightMotorGroup),
                                                   inchesToDegreesRatio(inchesToDegreesRatio)
{
  calibrateInertial();
  resetEncoders();
  odometry = new Odometry(this, forwardTrackerDistance, sidewaysTrackerDistance);
}

Chassis::~Chassis()
{
  delete odometry;
}

void Chassis::followPath(vector<Pose<double>> path, PursuitParams params)
{
  pursuit = new Pursuit(this, params);
  pursuit->followPath(path);
}

Angle<double> Chassis::getAbsoluteHeading()
{
  return Angle<double>((Inertial.heading(deg) * 360) / inertialScaling).constrain0To360();
}

Pair Chassis::getMotorVelocities(double driveOutput, double turnOutput)
{
  double left = driveOutput + turnOutput;
  double right = driveOutput - turnOutput;

  double sum = (driveOutput + turnOutput) / 12;
  if (sum > 1)
  {
    left /= sum;
    right /= sum;
  }

  return Pair(left, right);
}

Pair Chassis::getMotorsPosition()
{
  return Pair(Left.position(deg) * inchesToDegreesRatio, Right.position(deg) * inchesToDegreesRatio);
}

void Chassis::calibrateInertial()
{
  Inertial.calibrate();
  while (Inertial.isCalibrating())
    wait(50, msec);
  // Controller.rumble("..");
  cout << "Inertial calibrated" << endl;
}

void Chassis::resetEncoders()
{
  Left.resetPosition();
  Right.resetPosition();
  forwardTracker.resetPosition();
  sidewaysTracker.resetPosition();
}

double Chassis::getForwardTrackerPosition()
{
  return forwardTracker.position(deg) * inchesToDegreesRatio;
}

double Chassis::getSidewaysTrackerPosition()
{
  return sidewaysTracker.position(deg) * inchesToDegreesRatio;
}