#include "../include/utils.h"

template <class T>
int sgn(T number)
{
  if (number > 0)
    return 1;
  else if (number < 0)
    return -1;
  return 0;
}

template <class T>
T clamp(T value, T min, T max)
{
  if (value < min)
    value = min;
  else if (value > max)
    value = max;
  return value;
}

template <class T>
T clampMin(T value, T min)
{
  if (value < 0 && value > -min)
    return -min;
  else if (value > 0 && value < min)
    return min;
  return value;
}

template <class T>
T slew(T current, T target, T maxChange)
{
  T change = target - current;
  if (change > maxChange)
    change = maxChange;
  else if (change < -maxChange)
    change = -maxChange;
  return current + change;
}

template <class T>
T toVoltage(T percent)
{
  return (percent / 100) * 12;
}

double getSignedTangentArcCurvature(Pose<double> start, Vector2D<double> end)
{
  const Pose<double> delta = end - start.position;
  const Vector2D<double> normalVector = Vector2D<double>(sin(start.orientation.angle), cos(start.orientation.angle));
  const int side = sgn(delta.position.crossProduct(normalVector));

  // Calculate the center point of the circle and then the radius
  const double a = -tan(start.orientation.angle);
  const double c = tan(start.orientation.angle) * start.position.x - start.position.y;
  const double x = fabs(a * end.x + end.y * c) / sqrt(a * a + 1);
  const double d = start.position.distanceTo(end);

  return side * ((2 * x) / (d * d));
}