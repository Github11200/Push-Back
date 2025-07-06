#ifndef UTIL_H
#define UTIL_H

#include "vex.h"

using namespace std;
using namespace vex;

template <class T>
int sgn(T number)
{
  if (number > 0)
    return 1;
  else if (number < 0)
    return -1;
  return 0;
}

#endif UTIL_H