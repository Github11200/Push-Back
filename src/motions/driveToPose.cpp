#ifndef DRIVE_TO_POINT_H
#define DRIVE_TO_POINT_H

#include "../../include/chassis.h"

using namespace vex;
using namespace std;

void Chassis::driveToPose(Pose<double> target, DriveParams driveParams, TurnParams turnParams, Settings settings, double lead, double setback)
{
  PID drivePID(settings.updateTime, driveParams);
  PID turnPID(settings.updateTime, turnParams);

  Pose<double> currentPose;

  double driveOutput = 0;
  double turnOutput = 0;

  double previousDriveOutput = 0;
  double previousTurnOutput = 0;

  double headingScaleFactor = 0;

  bool isClose = false;
  bool previousSameSide = false;

  Vector2D<double> carrotPoint;
  double targetDistance = 0;
  double carrotX = 0;
  double carrotY = 0;

  while (!drivePID.isSettled() && !turnPID.isSettled())
  {
    currentPose = odometry.getPose();

    // TODO: Make the 7.0 dynamic or a parameter
    if (!isClose && odometry.getPose().position.distanceTo(target.position) <= 7.0)
    {
      isClose = true;
    }

    targetDistance = currentPose.position.distanceTo(target.position);
    carrotX = target.position.x - sin(target.orientation.toRad().angle) * (lead * targetDistance + setback);
    carrotY = target.position.y - cos(target.orientation.toRad().angle) * (lead * targetDistance + setback);
    carrotPoint = Vector2D<double>(carrotX, carrotY);

    double driveError = currentPose.position.distanceTo(carrotPoint);
    Angle<double> turnError = (currentPose.position.angleTo(carrotPoint) - getAbsoluteHeading()).constrainNegative180To180();

    headingScaleFactor = cos(turnError.toRad().angle);

    {
      // This is a visualization of what's happening here, https://www.desmos.com/calculator/apijy0bvki?lang=en
      Vector2D<double> projectedPerpendicularLine(-sin(target.orientation.toRad().angle), cos(target.orientation.toRad().angle));
      Vector2D<double> lineFromCurrentPositionToTarget(currentPose.position.x - target.position.x, currentPose.position.y - target.position.y);
      Vector2D<double> lineFromCarrotToTarget(carrotPoint.x - target.position.x, carrotPoint.y - target.position.y);

      // If it is less than 0 then it is before the target point, otherwise it is after
      const bool targetSide = projectedPerpendicularLine.crossProduct(lineFromCurrentPositionToTarget) <= driveParams.driveSettleError;

      // If it is less 0 then the carrot point is before the perpendicular line, and this is always the case
      const bool carrotSide = projectedPerpendicularLine.crossProduct(lineFromCarrotToTarget) <= driveParams.driveSettleError;

      const bool sameSide = targetSide == carrotSide;

      // If the bot is close to being settled, previously it was the same side and now it's not then it means the carrot point is behind
      // the perpendicular line and the robot is ahead of it, and sincce drive min voltage isn't 0 it'll start tweaking out so just exit
      if (isClose && previousSameSide && !sameSide && driveParams.driveMinVoltage != 0)
        break;
      previousSameSide = sameSide;
    }

    driveOutput = [&]() -> double
    {
      double output = 0;

      output = drivePID.compute(driveError) * headingScaleFactor;
      output = clamp(output, -driveParams.driveMaxVoltage, driveParams.driveMaxVoltage);
    }();

    turnOutput = turnPID.compute(turnError.angle);
    turnOutput = clamp(turnOutput, -turnParams.turnMinVoltage, turnParams.turnMaxVoltage);
  }

  Left.stop(hold);
  Right.stop(hold);
}

#endif