// #include "../../include/utils/bezier.h"

// using namespace std;
// using namespace vex;

// Vector2D<double> CubicBezier::point(double t)
// {
//   // P1 * (1 - t)^3 + P2 * 3 * (1 - t)^2 * t + P3 * 3 * (1 - t) * t^2 + P4 * t^3
//   return points[0] * pow((1 - t), 3) + points[1] * 3 * pow((1 - t), 2) * t + points[2] * 3 * (1 - t) * pow(t, 2) + points[3] * pow(t, 3);
// }

// Vector2D<double> CubicBezier::firstDerivative(double t)
// {
//   //
// }