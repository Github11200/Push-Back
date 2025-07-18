#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include "v5.h"
#include "v5_vcs.h"
#include "types/pose.h"

using namespace std;
using namespace vex;

template <class T>
int sgn(T number);

template <class T>
T clamp(T value, T min, T max);

template <class T>
T clampMin(T value, T min);

template <class T>
T slew(T current, T target, T maxChange);

template <class T>
T toVoltage(T percent);

// Visualization (still a work in progress): https://www.desmos.com/calculator/znrpd1hpwu
double getSignedTangentArcCurvature(Pose<double> start, Vector2D<double> end);

#endif