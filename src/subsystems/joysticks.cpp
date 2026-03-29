#include "subsystems/joysticks.h"

bool stopIsBrake = false;
bool CurveToggle = false;

double Joysticks::curve(double input, double curveValue)
{
  return (std::exp(-(curveValue / 10)) + std::exp((std::fabs(input) - 127) / 10) * (1 - std::exp(-(curveValue / 10)))) * input;
}

void Joysticks::control(double power, double turning)
{
  if (CurveToggle)
  {
    power = curve(deadband<double>(power, 1.0), 12);
    turning = curve(deadband<double>(turning, 1.0), 6);

    power = pow(power, 3) / pow(10, 4);
    turning = pow(turning, 3) / pow(10, 4);
  }
  else
  {
    power = deadband<double>(power, 0.5);
    turning = deadband<double>(turning, 0.05);
  }

  Pair outputs = getMotorVelocities(power, turning);

  if (outputs.left == 0 && stopIsBrake)
  {
    Left.stop(brake);
  }
  else
  {
    Left.stop(coast);
  }
  if (outputs.right == 0 && stopIsBrake)
  {
    Right.stop(brake);
  }
  else
  {
    Right.stop(coast);
  }

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