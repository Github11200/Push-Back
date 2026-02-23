#include "chassis.h"
#include "config.h"

using namespace vex;
using namespace std;

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
  return Pair(Left.position(vex::rotationUnits::deg) * Config::kMotorsInchesToDegreesRatio, Right.position(vex::rotationUnits::deg) * Config::kMotorsInchesToDegreesRatio);
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