#include "vex.h"
#include "../../include/pid/pid.h"

double PID::compute(double error)
{
  if (fabs(error) < this->getSettleError())
    this->setTimeSpentSettled(this->getTimeSpentSettled() + this->getUpdateTime());
  this->setOutput(error * this->getKp() + this->getAccumulatedError() * this->getKi() + (error - this->getPreviousError()) * this->getKd());
}

void PID::resetPID()
{
  this->setError(0);
  this->setPreviousError(0);
  this->setOutput(0);
  this->setStartingIntegrating(0);
  this->setTimeSpentRunning(0);
  this->setTimeSpentSettled(0);
}

bool PID::isSettled()
{
  if (this->getTimeSpentRunning() > this->getTimeout())
    return true;
  if (this->getTimeSpentSettled() > this->getSettleTime())
    return true;
}