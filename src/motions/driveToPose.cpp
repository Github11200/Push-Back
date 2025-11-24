#include "../../include/chassis.h"

using namespace vex;
using namespace std;

void Chassis::driveToPose(Pose<double> target, DriveParams driveParams, TurnParams turnParams, Settings settings, double lead, double setback, double driftCompensation)
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
    currentPose = odometry->getPose();

    // TODO: Make the 7.0 dynamic or a parameter
    if (!isClose && currentPose.position.distanceTo(target.position) <= 7.0)
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
      const bool robotSide = projectedPerpendicularLine.crossProduct(lineFromCurrentPositionToTarget) <= driveParams.driveSettleError;

      // If it is less 0 then the carrot point is before the perpendicular line, and this is always the case
      const bool carrotSide = projectedPerpendicularLine.crossProduct(lineFromCarrotToTarget) <= driveParams.driveSettleError;

      const bool sameSide = robotSide == carrotSide;

      // If the bot is close to being settled, previously it was the same side and now it's not then it means the carrot point is behind
      // the perpendicular line and the robot is ahead of it
      if (previousSameSide && !sameSide)
        break;
      previousSameSide = sameSide;
    }

    turnOutput = [&]() -> double
    {
      double output = 0;
      output = turnPID.compute(turnError.angle);

      // Clamp the values
      output = clamp(output, -turnParams.turnMaxVoltage, turnParams.turnMaxVoltage);
      output = clampMin(output, turnParams.turnMinVoltage);

      previousTurnOutput = output;
      return output;
    }();

    driveOutput = [&]() -> double
    {
      double output = 0;

      output = drivePID.compute(driveError) * headingScaleFactor;
      output = clamp(output, -driveParams.driveMaxVoltage * headingScaleFactor, driveParams.driveMaxVoltage * headingScaleFactor);

      // Limit accleration
      if (!isClose)
        output = slew(previousDriveOutput, output, driveParams.driveSlew);

      const double radius = 1 / abs(getSignedTangentArcCurvature(currentPose, carrotPoint));

      // // If the drift compensation is 0 that means it should be disabled
      if (driftCompensation != 0)
      {
        // The equation used here is the one for lateral acceleration in a turn, so a = v^2 / r. Here a is the drift compensation
        // so what the maximum lateral acceleration is and radius is the radius of the turn to get to the carrot point
        const double maxSlipSpeed = sqrt(driftCompensation * radius);
        output = clamp(output, -maxSlipSpeed, maxSlipSpeed);
      }

      // If this variable is positive then that means there's more of an emphasis on turning
      const double overTurnVoltage = abs(output) + abs(turnOutput) - driveParams.driveMaxVoltage;
      // Move the drive output closer to 0 so that there is more of an emphasis on turning
      if (overTurnVoltage > 0)
        output -= output > 0 ? overTurnVoltage : -overTurnVoltage;

      // Constrain to the minimum voltage
      output = clampMin(output, driveParams.driveMinVoltage);

      previousDriveOutput = output;
      return output;
    }();

    Pair outputs = getMotorVelocities(driveOutput, turnOutput);
    Left.spin(fwd, outputs.left, volt);
    Right.spin(fwd, outputs.right, volt);

    wait(settings.updateTime, msec);
  }

  cout << "GET THE HELL OUT, plase :)" << endl;

  Left.stop(hold);
  Right.stop(hold);
}