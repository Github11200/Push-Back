#include "chassis.h"

using namespace vex;
using namespace std;

void Chassis::driveWithVoltage(double power, double timeout, double heading, TurnParams turnParams, Settings settings)
{
  PID turnPID(settings.updateTime, turnParams);
  double elapsedTime = 0;

  while (elapsedTime < timeout)
  {
    double turnError = odometry->getPose().orientation.angleTo(heading).angle;
    double turnOutput = turnPID.compute(turnError);
    turnOutput = clamp<double>(turnOutput, -turnParams.turnMaxVoltage, turnParams.turnMaxVoltage);
    turnOutput = clampMin<double>(turnOutput, turnParams.turnMinVoltage);

    Pair motorOutputs = getMotorVelocities(power, turnOutput);
    Left.spin(fwd, motorOutputs.left, volt);
    Right.spin(fwd, motorOutputs.right, volt);

    wait(settings.updateTime, msec);
    elapsedTime += settings.updateTime;
  }

  Left.stop(brake);
  Right.stop(brake);
}