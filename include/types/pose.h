#ifndef POSE_H
#define POSE_H

#include "types/vector.h"

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

template <class T>
struct MotionProfilePose : Pose<T>
{
  double time;
  double velocity;
  double angularVelocity;
  double curvature;

  MotionProfilePose() = default;
  MotionProfilePose(double time,
                    double x,
                    double y,
                    Angle<T> angle,
                    double speed,
                    double acceleration,
                    double curvature) : time(time),
                                        Pose<T>(x, y, angle),
                                        velocity(speed),
                                        angularVelocity(acceleration),
                                        curvature(curvature) {}
};

#endif