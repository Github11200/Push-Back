#include "../include/chassis.h"

using namespace vex;
using namespace std;

Angle<double> Chassis::getAbsoluteHeading()
{
  return Angle<double>((Inertial.heading(deg) * 360) / inertialScaling);
}

pair<double, double> Chassis::getMotorVelocities(double driveOutput, double turnOutput)
{
  double left = driveOutput - turnOutput;
  double right = driveOutput + turnOutput;

  double sum = driveOutput + turnOutput;
  if (sum > 1)
  {
    left /= sum;
    right /= sum;
  }

  return pair<int, int>(toVoltage(left), toVoltage(right));
}