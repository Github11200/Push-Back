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
  double speed;
  double acceleration;

  constexpr MotionProfilePose() : Pose<T>(), speed(0), acceleration(0) {}

  constexpr MotionProfilePose(double x, double y, double speed, double acceleration) : Pose<T>(x, y), speed(speed), acceleration(acceleration) {}
  constexpr MotionProfilePose(double x, double y, double orientation, double speed, double acceleration) : Pose<T>(x, y, orientation), speed(speed), acceleration(acceleration) {}
  constexpr MotionProfilePose(double x, double y, Angle<T> angle, double speed, double acceleration) : Pose<T>(x, y, angle), speed(speed), acceleration(acceleration) {}
};

#endif