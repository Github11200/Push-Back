#ifndef PID_H
#define PID_H

#include "types/params.h"
#include "types/time.h"
#include "utils/utils.h"
#include "vex.h"

using namespace vex;
using namespace std;

/**
 * @brief
 *
 */
class PID
{
protected:
  double error = 0;
  double accumulatedError = 0;
  double previousError = 0;

  double kP = 0;
  double kI = 0;
  double kD = 0;

  double stopIntegratingLimit = 0;

  double timeout = 0;
  double timeSpentRunning = 0;
  double timeSpentSettled = 0;

  double settleError = 0;
  double settleTime = 0;

  double previousTime = -1;

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

  PID() {}
  PID(int updateTime, DriveParams driveParams) : kP(driveParams.driveKp),
                                                 kI(driveParams.driveKi),
                                                 kD(driveParams.driveKd),
                                                 stopIntegratingLimit(driveParams.driveStopIntegratingLimit),
                                                 timeout(driveParams.driveTimeout),
                                                 settleError(driveParams.driveSettleError),
                                                 settleTime(driveParams.driveSettleTime),
                                                 updateTime(updateTime) {}

  PID(int updateTime, TurnParams turnParams) : kP(turnParams.turnKp),
                                               kI(turnParams.turnKi),
                                               kD(turnParams.turnKd),
                                               stopIntegratingLimit(turnParams.turnStopIntegratingLimit),
                                               timeout(turnParams.turnTimeout),
                                               settleError(turnParams.turnSettleError),
                                               settleTime(turnParams.turnSettleTime),
                                               updateTime(updateTime) {}
};

#endif