#ifndef ANGLE_H
#define ANGLE_H

#include "vex.h"

using namespace vex;
using namespace std;

template <class T>
struct Angle
{
  T angle;

  constexpr Angle() : angle(0) {}
  constexpr Angle(T angle) : angle(angle) {}

  constexpr void toDeg() const { angle *= (180 / M_PI); }
  constexpr void toRad() const { angle /= (180 / M_PI); }
};

#endif