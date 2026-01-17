#include "chassis.h"

using namespace vex;
using namespace std;

void Chassis::turnTo(const Pose<double> &target, TurnParams params, Settings settings)
{
  PID turnPID(settings.updateTime, params);

  double turnOutput = 0;
  double previousTurnOutput = 0;

  Angle<double> turnError;
  Angle<double> previousTurnError = Angle<double>(-360);

  Pose<double> currentPose;

  double elapsedTime = 0;
  while (!turnPID.isSettled())
  {
    currentPose = odometry->getPose();

    Angle<double> additionalAngle = Angle<double>(settings.forwards ? 0 : -180);

    // If the angle is -360 that means we want to turn to a point
    if (target.orientation.angle == -360)
      turnError = (currentPose.position.angleTo(target.position) - currentPose.orientation + additionalAngle).constrainNegative180To180();
    else // we want to turn to an angle
      turnError = currentPose.orientation.angleTo(target.orientation);

    if (previousTurnError.angle == -360)
      previousTurnError = turnError;

    // If the min voltage isn't 0 and the robot is tweaking out then just exit
    if (sgn(previousTurnError.angle) != sgn(turnError.angle) && params.turnMinVoltage != 0)
      break;

    turnOutput = turnPID.compute(turnError.angle);

    turnOutput = clamp(turnOutput, -params.turnMaxVoltage, params.turnMaxVoltage);
    turnOutput = clampMin(turnOutput, params.turnMinVoltage);

    previousTurnOutput = turnOutput;

    // Make the motors move
    Left.spin(fwd, turnOutput, volt);
    Right.spin(fwd, -turnOutput, volt);

    if ((int)elapsedTime % 30 == 0 && settings.sendPositionData)
      Logger::sendMotionData(Logger::MotionType::TURN_TO_ANGLE, elapsedTime, abs(currentPose.orientation.constrainNegative180To180().angle));

    wait(settings.updateTime, msec);
    elapsedTime += settings.updateTime;
  }

  cout << "Turn done" << endl;
  Logger::sendMotionEnd(elapsedTime);
  Left.stop(hold);
  Right.stop(hold);
}