#ifndef TIMER_H
#define TIMER_H

#include "vex.h"

class Timer
{
private:
  time_t startTimestamp;
  struct tm startDateTime;

public:
  void startTimer();
  double stopTimer();
};

#endif