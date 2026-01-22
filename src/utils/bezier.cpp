// #include "utils/bezier.h"

// using namespace std;
// using namespace vex;

// CubicBezier::CubicBezier(Vector2D<double> points[4])
// {
//   this->points[0] = points[0];
//   this->points[1] = points[1];
//   this->points[2] = points[2];
//   this->points[3] = points[3];
// }

// Vector2D<double> CubicBezier::getPosition(double t)
// {
//   // P1 * (1 - t)^3 + P2 * 3 * (1 - t)^2 * t + P3 * 3 * (1 - t) * t^2 + P4 * t^3
//   return points[0] * pow((1 - t), 3) + points[1] * 3.0 * pow((1 - t), 2) * t + points[2] * 3.0 * (1 - t) * pow(t, 2) + points[3] * pow(t, 3);
// }

// Vector2D<double> CubicBezier::getFirstDerivative(double t)
// {
//   // 3*(1 - t)^2*(P1 - P0) + 6*(1 - t)*t*(P2 - P1) + 3*t^2*(P3 - P2)
//   return (points[1] - points[0]) * 3.0 * pow((1 - t), 2) + (points[2] - points[1]) * 6.0 * (1 - t) * t + (points[3] - points[2]) * 3.0 * pow(t, 2);
// }

// Vector2D<double> CubicBezier::getSecondDerivative(double t)
// {
//   // 6 * (1 - t) * (P_0 - 2 * P_1 + P_2) + 6 * t * (P_1 - 2 * P_2 + P_4)
//   return (points[0] - points[1] * 2.0 + points[2]) * 6.0 * (1 - t) + (points[1] - points[2] * 2.0 + points[3]) * 6.0 * t;
// }

// double CubicBezier::getCurvature(double t)
// {
//   Vector2D<double> firstDerivative = getFirstDerivative(t);
//   Vector2D<double> secondDerivative = getSecondDerivative(t);

//   double numerator = firstDerivative.x * secondDerivative.y - firstDerivative.y * secondDerivative.x;
//   double denominator = pow(firstDerivative.x * firstDerivative.x + firstDerivative.y * firstDerivative.y, 1.5);

//   return numerator / denominator;
// }

// double CubicBezier::getArcLength()
// {
//   double length = 0;
//   for (int i = 0; i < n; ++i)
//   {
//     double tau = ((b - a) * nodes[i]) / 2 + ((a + b) / 2);
//     length += weights[i] * getSecondDerivative(tau);
//   }
//   return length * (t / 2);
// }