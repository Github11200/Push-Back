#include "../../include/chassis.h"

using namespace vex;
using namespace std;

void Chassis::turnTo(Pose<double> target, TurnParams params, Settings settings)
{
  PID turnPID(settings.updateTime, params);

  double turnOutput = 0;
  double previousTurnOutput = 0;

  Angle<double> turnError;
  Angle<double> previousTurnError = Angle<double>(-360);

  Pose<double> currentPose;

  while (!turnPID.isSettled())
  {
    currentPose = odometry->getPose();

    Angle<double> additionalAngle = Angle<double>(settings.forwards ? 0 : 180);

    // If the angle is -360 that means we want to turn to a point
    if (target.orientation.angle == -360)
      turnError = (currentPose.position.angleTo(target.position) - currentPose.orientation + additionalAngle).constrainNegative180To180();
    else // we want to turn to an angle
      turnError = currentPose.orientation.angleTo(target.orientation).constrainNegative180To180();

    if (previousTurnError.angle == -360)
      previousTurnError = turnError;

    cout << turnError.angle << endl;
    // If the min voltage isn't 0 and the robot is tweaking out then just exit
    if (params.turnMinVoltage != 0 && sgn(previousTurnError.angle) != sgn(turnError.angle))
      break;

    turnOutput = [&]() -> double
    {
      double output = 0;
      output = turnPID.compute(turnError.angle);

      output = clamp(output, -params.turnMaxVoltage, params.turnMaxVoltage);
      output = clampMin(output, params.turnMinVoltage);

      previousTurnOutput = output;
      return output;
    }();

    Left.spin(fwd, turnOutput, volt);
    Right.spin(fwd, -turnOutput, volt);

    wait(settings.updateTime, msec);
  }

  Left.stop(brake);
  Right.stop(brake);
}