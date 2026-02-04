#include "utils/interpLUT.h"

using namespace std;
using namespace vex;

InterpolatedLUT::InterpolatedLUT(vector<Vector2D<double>> points)
{
  this->points = points;
  int n = points.size();

  vector<double> secants(n);
  for (int i = 0; i < n - 1; ++i)
  {
    double dy = points[i + 1].y - points[i].y;
    double dx = points[i + 1].x - points[i].x;
    secants[i] = dy / dx;
  }

  vector<double> slopes(n);
  slopes[0] = secants[0];
  for (int i = 1; i < n - 1; ++i)
    slopes[i] = (secants[i] + secants[i - 1]) / 2;
  slopes[slopes.size() - 1] = secants[secants.size() - 2];

  for (int i = 0; i < n - 1; ++i)
  {
    // No divide by zero errors :)
    if (secants[i] == 0)
    {
      slopes[i] = 0;
      slopes[i + 1] = 0;
    }
    else
    {
      double alpha = slopes[i] / secants[i];
      double beta = slopes[i + 1] / secants[i];
      double h = sqrt(pow(alpha, 2) + pow(beta, 2));
      if (h > 3)
      {
        double t = 3 / h;
        slopes[i] = (t * alpha) * secants[i];
        slopes[i + 1] = (t * beta) * secants[i];
      }
    }
  }

  this->slopes = slopes;
}

double InterpolatedLUT::hermite(double point, Pair x, Pair y, Pair slope)
{
  double h = x.second - x.first;
  double t = (point - x.first) / h;

  double left = (y.first * (1 + 2 * t) + h * slope.first * t) * pow((1 - t), 2);
  double right = (y.second * (3 - 2 * t) + h * slope.second * (t - 1)) * pow(t, 2);

  return left + right;
}

double InterpolatedLUT::interpolate(double point)
{
  if (point < points[0].x)
    return points[0].y;
  if (point > points.back().x)
    return points.back().y;

  int i = 0;
  while (point >= points[i + 1].x)
  {
    ++i;
    if (point == points[i].x)
      return points[i].y;
  }

  Pair xPair = Pair(points[i].x, points[i + 1].x);
  Pair yPair = Pair(points[i].y, points[i + 1].y);
  Pair slopePair = Pair(slopes[i], slopes[i + 1]);

  return hermite(point, xPair, yPair, slopePair);
}