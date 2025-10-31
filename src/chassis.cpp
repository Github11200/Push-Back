#include "../include/chassis.h"

using namespace vex;
using namespace std;

// TODO: Update the ports for all the sensors
Chassis::Chassis(int inertialPort,
                 TrackerSetup trackerSetup,
                 int forwardTrackerPort,
                 int sidewaysTrackerPort,
                 double inchesToDegreesRatio,
                 double forwardTrackerDistance,
                 double sidewaysTrackerDistance,
                 double frontDistanceSensorDistance,
                 double rightDistanceSensorDistance,
                 double leftDistanceSensorDistance,
                 double backDistanceSensorDistance,
                 bool enableLogs) : Inertial(inertial(inertialPort)),
                                    forwardTracker(forwardTrackerPort),
                                    sidewaysTracker(sidewaysTrackerPort),
                                    inchesToDegreesRatio(inchesToDegreesRatio)
{
  odometry = new Odometry(this,
                          forwardTrackerDistance,
                          sidewaysTrackerDistance,
                          frontDistanceSensorDistance,
                          rightDistanceSensorDistance,
                          leftDistanceSensorDistance,
                          backDistanceSensorDistance,
                          trackerSetup);
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

Pair Chassis::getMotorsPosition()
{
  // cout << Left.position(vex::rotationUnits::deg) << endl;
  inchesToDegreesRatio = 0.0205699519;
  return Pair(Left.position(vex::rotationUnits::deg) * inchesToDegreesRatio, Right.position(vex::rotationUnits::deg) * inchesToDegreesRatio);
}

void Chassis::calibrateInertial()
{
  Inertial.calibrate();
  while (Inertial.isCalibrating())
    wait(50, msec);
  Controller.rumble("..");
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