#include "../../include/subsystems/joysticks.h"

void Joysticks::control(double power, double turning)
{
  power = deadband<double>(power, 1.0) / 1.27;
  turning = deadband<double>(turning, 1.0) / 1.27;

  power = pow(power, 3) / pow(10, 4);
  turning = pow(turning, 3) / pow(10, 4);

  Pair outputs = getMotorVelocities(power, turning);

  Right.spin(vex::directionType::fwd, outputs.right, vex::voltageUnits::volt);
  Left.spin(vex::directionType::fwd, outputs.left, vex::voltageUnits::volt);
}

void Joysticks::arcade()
{
  control(Controller.Axis3.value(), Controller.Axis1.value());
}

void Joysticks::tank()
{
  control(Controller.Axis3.value(), Controller.Axis4.value());
}