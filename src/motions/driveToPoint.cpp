#ifndef DRIVE_TO_POINT_H
#define DRIVE_TO_POINT_H

#include "../../include/chassis.h"

using namespace vex;
using namespace std;

void Chassis::driveToPoint(Pose<double> target, DriveParams driveParams, TurnParams turnParams, Settings settings)
{
  PID drivePID(settings.updateTime, driveParams);
  PID turnPID(settings.updateTime, turnParams);

  Pose<double> currentPose = odometry.getPose();

  double driveOutput = 0;
  double turnOutput = 0;

  double previousDriveOutput = 0;
  double previousTurnOutput = 0;

  double headingScaleFactor = 0;

  bool isClose = false;
  int previousSide = -1; // -1 is null
  Angle<double> initialHeading = currentPose.position.angleTo(target.position);

  while (!drivePID.isSettled())
  {
    currentPose = odometry.getPose();

    // TODO: Make the 7.0 dynamic or a parameter
    if (!isClose && odometry.getPose().position.distanceTo(target.position) <= 7.0)
    {
      isClose = true;
      // TODO: Change the 4.5 to be a parameter or dynamic
      driveParams.driveMaxVoltage = max(fabs(previousDriveOutput), 4.5);
      turnParams.turnMaxVoltage = max(fabs(previousTurnOutput), 4.5);
    }

    double driveError = hypot(target.position.x - currentPose.position.x, target.position.y - currentPose.position.y);
    Angle<double> turnError = (currentPose.position.angleTo(target.position) - getAbsoluteHeading()).constrainNegative180To180();

    // TODO: Try seeing if there's another way you could scale it (using a different function perhaps?)
    /*
      What it's meant to do is that when the robot is facing perpendicular to the target (90 degrees) then
      cos(90) = 0 so there is no lateral movement, it focuses just on turning, but as it gets closer to the
     target, like 32 degrees, cos(the angle) will approach 1 meaning that there is more of an emphasis on
     the lateral rather than the angular movement
    */
    headingScaleFactor = cos(turnError.toRad().angle);

    {
      Vector2D<double> projectedPerpendicularLine(-sin(initialHeading.toRad().angle), cos(initialHeading.toRad().angle));
      Vector2D<double> lineFromCurrentPositionToTarget(currentPose.position.x - target.position.x, currentPose.position.y - target.position.y);

      // If the cross product is negative then it is before the line and if it is positive then it is after the line
      // https://www.desmos.com/calculator/apijy0bvki, this is a visualization of what's happening
      const bool side = lineFromCurrentPositionToTarget.crossProduct(projectedPerpendicularLine) <= driveParams.driveSettleError;
      if (previousSide == -1)
        previousSide = side;
      const bool sameSide = previousSide == side ? true : false;

      // If the robot crossed over this perpendicular line and the min drive voltage is not 0 then it'll
      // keep oscillating and not settle so instead just have it stop the motion
      if (!sameSide && driveParams.driveMinVoltage > 0)
        break;
      previousSide = side;
    }

    turnOutput = [&]() -> double
    {
      double output = 0;
      output = turnPID.compute(turnError.angle);

      // Clamp the values
      output = clamp(output, -turnParams.turnMaxVoltage, turnParams.turnMaxVoltage);
      output = clampMin(output, turnParams.turnMinVoltage);

      if (!isClose)
        output = slew(previousTurnOutput, turnOutput, turnParams.turnSlew);

      previousTurnOutput = output;
      return output;
    }();

    driveOutput = [&]() -> double
    {
      double output = 0;

      output = drivePID.compute(driveError) * headingScaleFactor;

      // CLamp it between min and max values
      output = clamp(output, -driveParams.driveMaxVoltage * headingScaleFactor, driveParams.driveMaxVoltage * headingScaleFactor);
      output = clampMin(output, driveParams.driveMinVoltage);

      if (isClose)
        output = slew(previousDriveOutput, output, driveParams.driveSlew);

      previousDriveOutput = output;
      return output;
    }();

    pair<double, double> motorOutputs = getMotorVelocities(driveOutput, turnOutput);
    Left.spin(fwd, motorOutputs.first, volt);
    Right.spin(fwd, motorOutputs.second, volt);

    wait(settings.updateTime, msec);
  }

  Left.stop(hold);
  Right.stop(hold);
}

#endif