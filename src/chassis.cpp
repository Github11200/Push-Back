#include "chassis.h"
#include "config.h"

using namespace vex;
using namespace std;

// TODO: Update the ports for all the sensors
Chassis::Chassis() : inertialScaling(Config::kInertialScaling),
                     forwardTrackerInchesToDegreesRatio(Config::kForwardTrackerInchesToDegreesRatio),
                     sidewaysTrackerInchesToDegreesRatio(Config::kSidewaysTrackerInchesToDegreesRatio)
{
  odometry = new Odometry(this);
}

Chassis::~Chassis()
{
  delete odometry;
}

// void Chassis::followPath(vector<Pose<double>> path, PursuitParams params)
// {
//   pursuit = new Pursuit(this, params);
//   pursuit->followPath(path);
// }

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
  ForwardTracker.resetPosition();
  SidewaysTracker.resetPosition();
}

double Chassis::getForwardTrackerPosition()
{
  return ForwardTracker.position(deg) * forwardTrackerInchesToDegreesRatio;
}

double Chassis::getSidewaysTrackerPosition()
{
  return SidewaysTracker.position(deg) * sidewaysTrackerInchesToDegreesRatio;
}