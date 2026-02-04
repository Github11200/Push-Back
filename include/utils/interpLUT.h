#ifndef INTERP_LUT_H
#define INTERP_LUT_H

#include "vex.h"
#include "types/vector.h"

#define Pair pair<double, double>

class InterpolatedLUT
{
private:
  std::vector<Vector2D<double>> points;
  std::vector<double> slopes;

  double hermite(double point, Pair x, Pair y, Pair slope);

public:
  InterpolatedLUT(std::vector<Vector2D<double>> points);

  double interpolate(double point);
};

#endif
