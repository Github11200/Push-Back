#include "../../include/utils/timer.h"

void Timer::startTimer()
{
  this->startTimestamp = time(&(this->startTimestamp));
  this->startDateTime = *localtime(&(this->startTimestamp));
}

double Timer::stopTimer()
{
  time_t endTimestamp = time(&endTimestamp);
  struct tm endDateTime = *localtime(&endTimestamp);
  return endDateTime.tm_sec - startDateTime.tm_sec;
}