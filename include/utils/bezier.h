#ifndef BEZIER_H
#define BEZIER_H

#include "vex.h"
#include "types/vector.h"

class CubicBezier
{
private:
  Vector2D<double> points[4];
  int n = 4;
  double nodes[4] = {-0.861136, -0.339981, 0.339981, -0.861136};
  double weights[4] = {0.347855, 0.652145, 0.652145, 0.347855};

public:
  CubicBezier() = default;
  CubicBezier(Vector2D<double> points[4]);

  Vector2D<double> getPosition(double t);
  Vector2D<double> getFirstDerivative(double t);
  Vector2D<double> getSecondDerivative(double t);
  double getCurvature(double t);
  double getArcLength(double t);
};

#endif