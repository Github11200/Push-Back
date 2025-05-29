#ifndef PID_H
#define PID_H

#include "vex.h"

using namespace vex;
using namespace std;

class PID
{
private:
  double error = 0;
  double previousError = 0;

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
  void compute();
};

#endif