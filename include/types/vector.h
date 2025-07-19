#ifndef VECTOR_H
#define VECTOR_H

#include "angle.h"

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
  constexpr T operator*(const Vector2D<T> &other) const { return (this->x * other.x) + (this->y * other.y); };
  constexpr Vector2D<T> operator/(double factor) const { return Vector2D<T>(this->x / factor, this->y / factor); };

  constexpr bool operator==(const Vector2D<T> &other) const { return (this->x == other.x) && (this->y == other.y); };
  constexpr bool operator!=(const Vector2D<T> &other) const { return (this->x != other.x) || (this->y != other.y); };

  constexpr T magnitude() const { return sqrt(this->x * this->x + this->y * this->y); }

  constexpr T distanceTo(const Vector2D<T> &other) const { return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2)); }
  constexpr Angle<T> angleTo(const Vector2D<T> &other) const { return Angle<T>(atan2(other.y - this->y, other.x - this->x)).toDeg().constrain0To360(); }

  constexpr T dot(const Vector2D<T> &other) const { return this->x * other.x + this->y * other.y; }
  constexpr T crossProduct(const Vector2D<T> &other) const { return this->x * other.y - other.x * this->y; }

  constexpr Vector2D<T> fromPolar(Angle<T> angle, T magnitude)
  {
    magnitude = abs(magnitude);
    angle.constrain0To360();
    return Vector2D<T>(cos(angle.toRad()) * magnitude, sin(angle.toRad()) * magnitude);
  }

  constexpr Vector2D<T> &rotateBy(Angle<T> angle) const { return fromPolar(Vector2D<T>({0, 0}).angleTo(*this) + angle, magnitude()); }

  constexpr Vector2D<T> normalize() const { return (*this) / magnitude(); }
};

#endif