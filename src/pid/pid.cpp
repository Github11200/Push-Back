#include "pid/pid.h"

double PID::compute(double error)
{
  // If the previous time is -1 then this is the very first iteration (woah)
  double currentTime = vex::timer::system();
  double dt = previousTime == -1 ? 0 : currentTime - previousTime;
  previousTime = currentTime;

  double derivative = dt != 0 ? (error - previousError) / dt : 0;
  previousError = error;

  if (fabs(error) < startIntegratingLimit)
    accumulatedError += error * dt;

  if (fabs(error) < settleError)
    timeSpentSettled += dt;
  else
    timeSpentSettled = 0;

  // If the robot is tweaking out and oscilating then get rid of the integral
  if (sgn(error) != sgn(previousError))
    accumulatedError = 0;
  // if (error <= startIntegratingLimit)
  //   accumulatedError = 0;

  timeSpentRunning += dt;

  return error * kP + accumulatedError * kI + derivative * kD;
}

void PID::resetPID()
{
  error = 0;
  previousError = 0;
  startIntegratingLimit = 0;
  timeSpentRunning = 0;
  timeSpentSettled = 0;
}

bool PID::isSettled()
{
  if (timeSpentRunning > timeout)
    return true;
  if (timeSpentSettled > settleTime)
    return true;
  return false;
}