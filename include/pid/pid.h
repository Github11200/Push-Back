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

  double stopIntegratingLimit = 0;

  double timeout = 0;
  double timeSpentRunning = 0;
  double timeSpentSettled = 0;

  double settleError = 0;
  double settleTime = 0;

  double updateTime = 0;

public:
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