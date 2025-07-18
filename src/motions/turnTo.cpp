#ifndef TURN_TO_POINT_H
#define TURN_TO_POINT_H

#include "../../include/chassis.h"

using namespace vex;
using namespace std;

void Chassis::turnTo(Pose<double> target, TurnParams params, Settings settings)
{
  PID turnPID(settings.updateTime, params);

  double angularOutput = 0;
  double previousAngularOutput = 0;

  Angle<double> turnError;
  Angle<double> previousTurnError = Angle<double>(-360);

  Pose<double> currentPose;

  while (!turnPID.isSettled())
  {
    currentPose = odometry.getPose();

    // If the angle is -360 that means we want to turn to a point
    if (target.orientation.angle == -360)
      turnError = (currentPose.position.angleTo(target.position).constrain0To360() - getAbsoluteHeading()).constrainNegative180To180();
    else // we want to turn to an angle
      turnError = currentPose.orientation.angleTo(target.orientation);

    if (previousTurnError.angle == -360)
      previousTurnError = turnError;

    // If the min voltage isn't 0 and the robot is tweaking out then just exit
    if (params.turnMinVoltage != 0 && sgn(previousTurnError) != sgn(turnError))
      break;

    angularOutput = turnPID.compute(turnError.angle);

    // Clamp the values
    angularOutput = clamp(angularOutput, params.turnMinVoltage, params.turnMaxVoltage);

    previousAngularOutput = angularOutput;

    Left.spin(fwd, -toVoltage(angularOutput), volt);
    Right.spin(fwd, toVoltage(angularOutput), volt);

    wait(settings.updateTime, msec);
  }

  Left.stop(hold);
  Right.stop(hold);
}

#endif