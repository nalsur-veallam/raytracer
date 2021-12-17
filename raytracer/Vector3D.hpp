#ifndef RAYTRACER_VECTOR3D_HPP
#define RAYTRACER_VECTOR3D_HPP

#include <math.h>

class Vector3D;
namespace math {

template <typename T>
struct Vector3D {
  T x, y, z;

  Vector3D<T>& operator+=(Vector3D<T> other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  Vector3D<T>& operator-=(Vector3D<T> other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }
};

template <typename T>
Vector3D<T> operator-(const Vector3D<T>& a, const Vector3D<T>& b) {
  Vector3D<T> out = a;
  return out -= b;
}

template <typename T>
Vector3D<T> operator+(const Vector3D<T>& a, const Vector3D<T>& b) {
  Vector3D<T> out = a;
  return out += b;
}

template <typename T>
T operator*(const Vector3D<T>& a, const Vector3D<T>& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
Vector3D<T> operator%(const Vector3D<T>& a, const Vector3D<T>& b) {
  return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

template <typename T>
Vector3D<T> operator*(const Vector3D<T>& v, T c) {
  return {v.x * c, v.y * c, v.z * c};
}

template <typename T>
Vector3D<T> operator*(T c, const Vector3D<T>& v) {
  return v * c;
}

template <typename T>
Vector3D<T> operator/(const Vector3D<T>& v, T c) {
  return {v.x / c, v.y / c, v.z / c};
}

template <typename T>
Vector3D<T> Norm(const Vector3D<T>& v) {
  return v / Abs(v);
}

template <typename T>
T Abs2(Vector3D<T> v) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}

template <typename T>
T Abs(Vector3D<T> v) {
  return std::sqrt(Abs2(v));
}

template <typename T>
std::ostream& operator<<(std::ostream& out, Vector3D<T> v) {
  out << v.x << " " << v.y << " " << v.z;
  return out;
}

template <typename T>
struct Ray {
  Vector3D<T> point, direction;
};

}  // namespace math

#endif RAY_TRACER_VECTOR3D_HPP
