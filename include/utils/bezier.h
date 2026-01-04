#ifndef BEZIER_H
#define BEZIER_H

#include "vex.h"
#include "types/vector.h"

class CubicBezier
{
private:
  Vector2D<double> points[4];

public:
  CubicBezier(Vector2D<double> points[4]);

  Vector2D<double> getPosition(double t);
  Vector2D<double> getFirstDerivative(double t);
  Vector2D<double> getSecondDerivative(double t);
  double getCurvature(double t);
};

#endif