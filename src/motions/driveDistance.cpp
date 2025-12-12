#include "chassis.h"

using namespace vex;
using namespace std;

void Chassis::driveDistance(double distance, double heading, DriveParams driveParams, TurnParams turnParams, Settings settings)
{
  PID drivePID(settings.updateTime, driveParams);
  PID turnPID(settings.updateTime, turnParams);

  double startingPosition = getForwardTrackerPosition();
  double position = startingPosition;
  while (!drivePID.isSettled())
  {
    position = getForwardTrackerPosition();
    double driveError = distance + startingPosition - position;
    double turnError = odometry->getPose().orientation.angleTo(heading).angle;

    double driveOutput = drivePID.compute(driveError);
    double turnOutput = turnPID.compute(turnError);

    if (!settings.forwards)
      driveOutput = clamp(driveOutput, -driveParams.driveMaxVoltage, -driveParams.driveMinVoltage);
    else
      driveOutput = clamp(driveOutput, driveParams.driveMinVoltage, driveParams.driveMaxVoltage);

    turnOutput = clamp<double>(turnOutput, -turnParams.turnMaxVoltage, turnParams.turnMaxVoltage);
    turnOutput = clampMin<double>(turnOutput, turnParams.turnMinVoltage);

    Pair motorOutputs = getMotorVelocities(driveOutput, turnOutput);
    Left.spin(fwd, motorOutputs.left, volt);
    Right.spin(fwd, motorOutputs.right, volt);

    wait(settings.updateTime, msec);
  }

  Left.stop(brake);
  Right.stop(brake);
}