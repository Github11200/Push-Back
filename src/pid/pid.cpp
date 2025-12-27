#include "pid/pid.h"

double PID::compute(double error)
{
  if (fabs(error) < settleError)
    timeSpentSettled += updateTime;
  else
    timeSpentSettled = 0;

  // If the robot is tweaking out and oscilating then get rid of the integral
  if (sgn(error) != sgn(previousError))
    accumulatedError = 0;

  if (error < startIntegratingLimit)
    accumulatedError += error;
  else
    accumulatedError = 0;

  output = error * kP + accumulatedError * kI + (error - previousError) * kD;

  timeSpentRunning += updateTime;
  previousError = error;

  return output;
}

void PID::resetPID()
{
  error = 0;
  previousError = 0;
  output = 0;
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