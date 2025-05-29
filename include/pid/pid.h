#ifndef PID_H
#define PID_H

#include "vex.h"

using namespace vex;
using namespace std;

/**
 * @brief
 *
 */
class PID
{
private:
  double error = 0;
  double accumulatedError = 0;
  double previousError = 0;
  double output = 0;

  double kP = 0;
  double kI = 0;
  double kD = 0;

  double turnkP = 0;
  double turnkI = 0;
  double turnkD = 0;

  double startingIntegrating = 0;

  double timeout = 0;
  double timeSpentRunning = 0;
  double timeSpentSettled = 0;

  double settleError = 0;
  double settleTime = 0;

  double updateTime = 0;

public:
  /**
   * @brief Update the local variables based on the new information
   *
   */

  // Getters
  double getError() const { return error; }
  double getAccumulatedError() const { return accumulatedError; }
  double getPreviousError() const { return previousError; }
  double getOutput() const { return output; }
  double getKp() const { return kP; }
  double getKi() const { return kI; }
  double getKd() const { return kD; }
  double getTurnKp() const { return turnkP; }
  double getTurnKi() const { return turnkI; }
  double getTurnKd() const { return turnkD; }
  double getStartingIntegrating() const { return startingIntegrating; }
  double getTimeout() const { return timeout; }
  double getTimeSpentRunning() const { return timeSpentRunning; }
  double getTimeSpentSettled() const { return timeSpentSettled; }
  double getSettleError() const { return settleError; }
  double getSettleTime() const { return settleTime; }
  double getUpdateTime() const { return updateTime; }

  // Setters
  void setError(double value) { error = value; }
  void setAccumulatedError(double value) { accumulatedError = value; }
  void setPreviousError(double value) { previousError = value; }
  void setOutput(double value) { output = value; }
  void setStartingIntegrating(double value) { startingIntegrating = value; }
  void setTimeout(double value) { timeout = value; }
  void setTimeSpentRunning(double value) { timeSpentRunning = value; }
  void setTimeSpentSettled(double value) { timeSpentSettled = value; }
  void setSettleError(double value) { settleError = value; }
  void setSettleTime(double value) { settleTime = value; }
  void setUpdateTime(double value) { updateTime = value; }

  /**
   * @brief Compute the new values such as time spent running, error, etc.
   *
   */
  double compute(double error);

  /**
   * @brief Reset all the values in the PID back to 0 other than the constants
   *
   */
  void resetPID();

  /**
   * @brief Check if the PID is settled by look at the timeout or settle time
   *
   */
  bool isSettled();
};

#endif