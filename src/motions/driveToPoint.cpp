#include "chassis.h"

using namespace vex;
using namespace std;

void Chassis::driveToPoint(const Pose<double> &target, DriveParams driveParams, TurnParams turnParams, Settings settings)
{
  PID drivePID(settings.updateTime, driveParams);
  PID turnPID(settings.updateTime, turnParams);

  Pose<double> currentPose = odometry->getPose();

  double driveOutput = 0;
  double turnOutput = 0;

  double previousDriveOutput = 0;
  double previousTurnOutput = 0;

  double headingScaleFactor = 0;

  bool isClose = false;
  int previousSide = -1; // -1 is null
  Angle<double> initialHeading = currentPose.position.angleTo(target.position);

  Logger::sendMotionStart(Logger::MotionType::DRIVE_TO_POINT, Logger::MotionData(target, driveParams, turnParams));

  Vector2D<double> projectedPerpendicularLine(-sin(initialHeading.toRad().angle), cos(initialHeading.toRad().angle));
  Angle<double> additionalAngle = Angle<double>(!settings.forwards ? 180 : 0);

  double elapsedTime = 0;
  while (!drivePID.isSettled())
  {
    currentPose = odometry->getPose();

    double distanceToTarget = currentPose.position.distanceTo(target.position);

    // If the distance is less than 7.5 then limit the max drive voltage and the max turn voltage can follow a sigmoid function
    if (distanceToTarget <= 7.5)
    {
      if (!isClose)
      {
        isClose = true;
        driveParams.driveMaxVoltage = max(fabs(previousDriveOutput), 4.7);
      }
      turnParams.turnMaxVoltage = sigmoid(distanceToTarget, 2, -0.2, 1);
    }

    double driveError = distanceToTarget;

    Angle<double> rawTurnError = currentPose.position.angleTo(target.position) - currentPose.orientation;
    Angle<double> turnError = (rawTurnError + additionalAngle).constrainNegative180To180();

    // TODO: Try seeing if there's another way you could scale it (using a different function perhaps?)
    /*
      What it's meant to do is that when the robot is facing perpendicular to the target (90 degrees) then
      cos(90) = 0 so there is no lateral movement, it focuses just on turning, but as it gets closer to the
      target, like 32 degrees, cos(the angle) will approach 1 meaning that there is more of an emphasis on
      the lateral rather than the angular movement
    */
    headingScaleFactor = cos(rawTurnError.constrainNegative180To180().toRad().angle);

    {
      Vector2D<double> lineFromCurrentPositionToTarget(currentPose.position.x - target.position.x, currentPose.position.y - target.position.y);

      // If the cross product is negative then it is before the line and if it is positive then it is after the line
      // https://www.desmos.com/calculator/apijy0bvki, this is a visualization of what's happening
      const bool side = lineFromCurrentPositionToTarget.crossProduct(projectedPerpendicularLine) <= driveParams.driveSettleError;
      if (previousSide == -1)
        previousSide = side;
      const bool sameSide = previousSide == side;

      // If the robot crossed over this perpendicular line and the min drive voltage is not 0 then it'll
      // keep oscillating and not settle so instead just have it stop the motion
      if (!sameSide && driveParams.driveMinVoltage > 0)
        break;
      previousSide = side;
    }

    /*=============================
                Turning
    =============================*/

    turnOutput = turnPID.compute(turnError.angle);

    // Clamp the values
    turnOutput = clamp(turnOutput, -turnParams.turnMaxVoltage, turnParams.turnMaxVoltage);
    turnOutput = clampMin(turnOutput, turnParams.turnMinVoltage);

    if (!isClose)
      turnOutput = slew(previousTurnOutput, turnOutput, turnParams.turnSlew);

    previousTurnOutput = turnOutput;

    /*=============================
                Driving
    =============================*/

    driveOutput = drivePID.compute(driveError) * headingScaleFactor;
    driveOutput = clamp(driveOutput, -driveParams.driveMaxVoltage * fabs(headingScaleFactor), driveParams.driveMaxVoltage * fabs(headingScaleFactor));
    driveOutput = clampMin<double>(driveOutput, driveParams.driveMinVoltage);

    if (!isClose)
      driveOutput = slew(previousDriveOutput, driveOutput, driveParams.driveSlew);

    if ((int)elapsedTime % 50 == 0)
      Logger::sendMotionData(Logger::MotionType::DRIVE_TO_POINT, elapsedTime, currentPose.orientation.constrainNegative180To180().angle, currentPose.position.y);

    previousDriveOutput = driveOutput;

    // Make it move
    Pair motorOutputs = getMotorVelocities(driveOutput, turnOutput);
    Left.spin(fwd, motorOutputs.left, volt);
    Right.spin(fwd, motorOutputs.right, volt);

    wait(settings.updateTime, msec);
    elapsedTime += settings.updateTime;

    if (Controller.ButtonA.pressing())
    {
      cout << odometry->getPose().position.y << endl;
    }
  }

  cout << "done" << endl;

  Left.stop(coast);
  Right.stop(coast);
}