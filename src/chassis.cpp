#include "../include/chassis.h"

using namespace vex;
using namespace std;

// TODO: Update the ports for all the sensors
Chassis::Chassis(int inertialPort,
                 double inertialScaling,
                 TrackerSetup trackerSetup,
                 int forwardTrackerPort,
                 int sidewaysTrackerPort,
                 double forwardTrackerInchesToDegreesRatio,
                 double sidewaysTrackerInchesToDegreesRatio,
                 double forwardTrackerDistance,
                 double sidewaysTrackerDistance,
                 double frontDistanceSensorDistance,
                 double rightDistanceSensorDistance,
                 double leftDistanceSensorDistance,
                 double backDistanceSensorDistance,
                 bool enableLogs) : Inertial(inertial(inertialPort)),
                                    inertialScaling(inertialScaling),
                                    forwardTracker(forwardTrackerPort),
                                    sidewaysTracker(sidewaysTrackerPort),
                                    forwardTrackerInchesToDegreesRatio(forwardTrackerInchesToDegreesRatio),
                                    sidewaysTrackerInchesToDegreesRatio(sidewaysTrackerInchesToDegreesRatio)
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
  return Angle<double>(Inertial.rotation(deg) * (360 / inertialScaling)).constrain0To360();
}

Pair Chassis::getMotorsPosition()
{
  // TODO: Create a seperate inches to degrees ratio for motor positions
  return Pair(Left.position(vex::rotationUnits::deg) * 0, Right.position(vex::rotationUnits::deg) * 0);
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
  return forwardTracker.position(deg) * forwardTrackerInchesToDegreesRatio;
}

double Chassis::getSidewaysTrackerPosition()
{
  return sidewaysTracker.position(deg) * sidewaysTrackerInchesToDegreesRatio;
}