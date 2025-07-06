#ifndef VECTOR_H
#define VECTOR_H

#include "vex.h"

using namespace vex;
using namespace std;

template <class T>
struct Vector2D
{
  T x, y;

  constexpr Vector2D() : x(0), y(0) {}
  constexpr Vector2D(T x, T y) : x(x), y(y) {}

  constexpr Vector2D<T> operator+(const Vector2D<T> &other) const { return Vector2D<T>(this->x + other.x, this->y + other.y); };
  constexpr Vector2D<T> operator-(const Vector2D<T> &other) const { return Vector2D<T>(this->x - other.x, this->y - other.y); };
  constexpr Vector2D<T> operator*(double factor) const { return Vector2D<T>(this->x * factor, this->y * factor); };
  constexpr double operator*(const Vector2D<T> &other) const { return (this->x * other.x) + (this->y * other.y); };
  constexpr Vector2D<T> operator/(double factor) const { return Vector2D<T>(this->x / factor, this->y / factor); };

  constexpr bool operator==(const Vector2D<T> &other) const { return (this->x == other.x) && (this->y == other.y); };
  constexpr bool operator!=(const Vector2D<T> &other) const { return (this->x != other.x) || (this->y != other.y); };

  constexpr T magnitude() const { return sqrt(this->x * this->x + this->y * this->y); }

  constexpr T distanceTo(const Vector2D<T> &other) const { return sqrt(pow(this->x - other.x) + pow(this->y - other.y)); }

  constexpr Vector2D<T> normalize() const { return (*this) / magnitude(); }
};

#endif