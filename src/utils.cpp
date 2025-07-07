#include "../include/utils.h"

template <class T>
int sgn(T number)
{
  if (number > 0)
    return 1;
  else if (number < 0)
    return -1;
  return 0;
}

template <class T>
T clamp(T value, T min, T max)
{
  if (value < min)
    value = min;
  else if (value > max)
    value = max;
  return value;
}

template <class T>
T slew(T current, T target, T maxChange)
{
  T change = target - current;
  if (change > maxChange)
    change = maxChange;
  else if (change < -maxChange)
    change = -maxChange;
  return current + change;
}