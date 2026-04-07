#include "subsystems/joysticks.h"

double Joysticks::curve(double input, double curveValue)
{
  return (std::exp(-(curveValue / 10)) + std::exp((std::fabs(input) - 127) / 10) * (1 - std::exp(-(curveValue / 10)))) * input;
}

void Joysticks::control(double power, double turning)
{
  // New drive curve :)
  power = curve(deadband<double>(power, 1.0), 12);
  turning = curve(deadband<double>(turning, 1.0), 6);

  power = pow(power, 3) / pow(10, 4);
  turning = pow(turning, 3) / pow(10, 4);

  if (abs(power) < 0.01 && abs(turning) > 0.1)
    if (abs(turning) < 2)
      turning = 2 * sgn(turning);

  Pair outputs = getMotorVelocities(power, turning);

  if (outputs.left == 0)
    Left.stop(brake);
  if (outputs.right == 0)
    Right.stop(brake);

  Right.spin(vex::directionType::fwd, outputs.right * 1.01, vex::voltageUnits::volt);
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