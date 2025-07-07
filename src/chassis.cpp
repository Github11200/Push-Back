#include "vex.h"
#include "../include/chassis.h"

using namespace vex;
using namespace std;

Angle<double> Chassis::getAbsoluteHeading()
{
  return Angle<double>((Inertial.heading(vex::rotationUnits::deg) * 360) / inertialScaling);
}