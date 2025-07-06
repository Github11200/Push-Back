#ifndef POSE_H
#define POSE_H

#include "vex.h"

using namespace vex;
using namespace std;

template <class T>
struct Pose
{
  Vector2D<T> position;
  Angle<T> orientation;

  constexpr Pose() : position(Vector2D()), orientation(Angle()) {}
  constexpr Pose(Vector2D vector) : position(vector), orientation(Angle()) {}
  constexpr Pose(Vector2D vector, double orientation) : position(vector), orientation(Angle(orientation)) {}
  constexpr Pose(double x, double y) : position(Vector2D(x, y)), orientation(Angle()) {}
  constexpr Pose(double x, double y, double orientation) : position(Vector2D(x, y)), orientation(orientation) {}
};

#endif