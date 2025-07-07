#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include "v5.h"
#include "v5_vcs.h"

using namespace std;
using namespace vex;

template <class T>
int sgn(T number);

template <class T>
T clamp(T value, T min, T max);

template <class T>
T slew(T current, T target, T maxChange);

#endif UTIL_H