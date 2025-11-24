#ifndef BEZIER_H
#define BEZIER_H

#include "vex.h"
#include "types/vector.h"

class CubicBezier
{
private:
  Vector2D<double> points[4];

public:
  CubicBezier(Vector2D<double> points[4]) : points(points) {};

  Vector2D<double> point(double t);
  Vector2D<double> firstDerivative(double t);
  Vector2D<double> secondDerivative(double t);
};

#endif