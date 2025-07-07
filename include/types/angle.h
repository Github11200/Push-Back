#ifndef ANGLE_H
#define ANGLE_H

#define RADIANS (180.0 / M_PI)

#include "math.h"

using namespace std;

template <class T>
struct Angle
{
  // By default the angle is in DEGREES
  T angle;

  constexpr Angle() : angle(0) {}
  constexpr Angle(T angle) : angle(angle) {}

  constexpr Angle<T> operator-(const Angle<T> &other) const { return Angle<T>(angle - other.angle); }
  constexpr Angle<T> operator+(const Angle<T> &other) const { return Angle<T>(angle + other.angle); }

  constexpr Angle<T> toDeg() const { return Angle<T>(angle * RADIANS); }
  constexpr Angle<T> toRad() const { return Angle<T>(angle / RADIANS); }

  // Constrains to [0, 360)
  constexpr Angle<T> constrain0To360() const
  {
    T tempAngle = this->angle;
    while (tempAngle < 0 || tempAngle >= 360)
    {
      if (tempAngle < 0)
        tempAngle += 360;
      else if (tempAngle >= 360)
        tempAngle -= 360;
    }
    return tempAngle;
  }

  // Constrains to [-180, 180)
  constexpr Angle<T> constrainNegative180To180() const
  {
    T tempAngle = this->angle;
    while (tempAngle < -180 || tempAngle >= 180)
    {
      if (tempAngle < -180)
        tempAngle += 360;
      else if (tempAngle >= 180)
        tempAngle -= 360;
    }
    return tempAngle;
  }
};

#endif