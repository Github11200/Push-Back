#ifndef POSE_H
#define POSE_H

#include "vector.h"

using namespace std;

template <class T>
struct Pose
{
  Vector2D<T> position;
  Angle<T> orientation;

  constexpr Pose() : position(Vector2D<T>()), orientation(Angle<T>()) {}

  constexpr Pose(Vector2D<T> vector) : position(vector), orientation(Angle<T>()) {}
  constexpr Pose(Vector2D<T> vector, double orientation) : position(vector), orientation(Angle<T>(orientation)) {}

  constexpr Pose(double x, double y) : position(Vector2D<T>(x, y)), orientation(Angle<T>()) {}
  constexpr Pose(double x, double y, double orientation) : position(Vector2D<T>(x, y)), orientation(orientation) {}
  constexpr Pose(double x, double y, Angle<T> angle) : position(Vector2D<T>(x, y)), orientation(angle) {}
};

#endif