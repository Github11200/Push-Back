#ifndef DRIVE_TO_POINT_H
#define DRIVE_TO_POINT_H

#include "../../include/chassis.h"

using namespace vex;
using namespace std;

void Chassis::driveToPoint(Pose<double> target, DriveParams driveParams, TurnParams turnParams, Settings settings)
{
  PID drive(settings.updateTime, driveParams);
  PID angular(settings.updateTime, turnParams);

  Pose<double> currentPose;

  double driveOutput = 0;
  double angularOutput = 0;

  double previousDriveOutput = 0;
  double previousAngularOutput = 0;

  double headingScaleFactor = 0;

  bool isClose = false;
  Angle<double> initialHeading;

  while (!drive.isSettled() && !angular.isSettled())
  {
    currentPose = odometry.getPose();

    // TODO: Make the 7.0 dynamic or a parameter
    if (!isClose && odometry.getPose().position.distanceTo(target.position) <= 7.0)
    {
      isClose = true;
      // TODO: Change the 4.5 to be a parameter or dynamic
      driveParams.driveMaxVoltage = max(abs(previousDriveOutput), 4.5);
      turnParams.turnMaxVoltage = max(abs(previousAngularOutput), 4.5);
    }

    double lateralError = hypot(target.position.x - currentPose.position.x, target.position.y - currentPose.position.y);
    Angle<double> angularError = ((currentPose.position.angleTo(target.position).toDeg()) - getAbsoluteHeading()).constrainNegative180To180();

    // TODO: Try seeing if there's another way you could scale it (using a different function perhaps?)

    /*
      What it's meant to do is that when the robot is facing perpendicular to the target (90 degrees) then
      cos(90) = 0 so there is no lateral movement, it focuses just on turning, but as it gets closer to the
     target, like 32 degrees, cos(the angle) will approach 1 meaning that there is more of an emphasis on
     the lateral rather than the angular movement
    */
    headingScaleFactor = cos(angularError.toRad().angle);

    {
      Vector2D<double> projectedPerpendicularLine(-sin(initialHeading.toRad().angle), cos(initialHeading.toRad().angle));
      Vector2D<double> lineFromCurrentPositionToTarget(currentPose.position.x - target.position.x, currentPose.position.y - target.position.y);

      // false = before the line, true = after the line
      const bool side = lineFromCurrentPositionToTarget.crossProduct(projectedPerpendicularLine) <= driveParams.driveSettleError;
    }

    driveOutput = drive.compute(lateralError) * headingScaleFactor;
    angularOutput = angular.compute(angularError.angle);

    // clamp the values
    driveOutput = clamp(driveOutput, driveParams.driveMinVoltage * headingScaleFactor, driveParams.driveMaxVoltage * headingScaleFactor);
    angularOutput = clamp(angularOutput, turnParams.turnMinVoltage, turnParams.turnMaxVoltage);

    // add in the slews
    driveOutput = slew(previousDriveOutput, driveOutput, driveParams.driveSlew);
    angularOutput = slew(previousAngularOutput, angularOutput, driveParams.driveSlew);

    previousDriveOutput = driveOutput;
    previousAngularOutput = angularOutput;

    wait(settings.updateTime, vex::timeUnits::msec);
  }
}

#endif