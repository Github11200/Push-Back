#include "../../include/utils/utils.h"
#include <iostream>

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
  return (percent / 100.0) * 12.0;
}

template <class T>
Vector2D<T> lerp(Vector2D<T> startPoint, Vector2D<T> endPoint, T t)
{
  return startPoint + Vector2D<double>((endPoint - startPoint).x * t, (endPoint - startPoint).y * t);
}

// TODO: Make sure this sign convention is consistent, curving to the left is negative and curving to the right is positive
double getSignedTangentArcCurvature(Pose<double> start, Vector2D<double> end)
{
  const Pose<double> delta = end - start.position;
  const Vector2D<double> normalVector = Vector2D<double>(cos(start.orientation.angle), sin(start.orientation.angle));
  const int side = sgn<double>(delta.position.crossProduct(normalVector));

  // Calculate the center point of the circle and then the radius
  const double a = -tan(start.orientation.angle);
  const double c = tan(start.orientation.angle) * start.position.x - start.position.y;
  const double x = fabs(a * end.x + end.y + c) / sqrt(a * a + 1);
  const double d = start.position.distanceTo(end);

  return side * ((2 * x) / (d * d));
}

double sigmoid(double x, double fractionalCoefficient, double exponentialCoefficient, double constant)
{
  return fractionalCoefficient * (1 / (1 + exp(x * exponentialCoefficient))) - constant;
}

// Explicit template instantiations for commonly used types
template int sgn<int>(int number);
template int sgn<double>(double number);
template int sgn<float>(float number);

template int clamp<int>(int value, int min, int max);
template double clamp<double>(double value, double min, double max);
template float clamp<float>(float value, float min, float max);

template int clampMin<int>(int value, int min);
template double clampMin<double>(double value, double min);
template float clampMin<float>(float value, float min);

template int slew<int>(int current, int target, int maxChange);
template double slew<double>(double current, double target, double maxChange);
template float slew<float>(float current, float target, float maxChange);

template int toVoltage<int>(int percent);
template double toVoltage<double>(double percent);
template float toVoltage<float>(float percent);

template Vector2D<double> lerp(Vector2D<double> startPoint, Vector2D<double> endPoint, double t);