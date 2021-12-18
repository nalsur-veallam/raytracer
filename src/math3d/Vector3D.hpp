#ifndef RAYTRACER_VECTOR3D_HPP
#define RAYTRACER_VECTOR3D_HPP

#include <math.h>
#include <random>

class Vector3D;
namespace math3d {

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
Vector3D<T> NormAndRotate90(Vector3D<T> v) {
  Vector3D<T> ex = {1, 0, 0};
  Vector3D<T> ey = {1, 0, 0};
  if (abs(ex * v) < abs(ey * v)) {
    return Norm(ex % v);
  } else {
    return Norm(ey % v);
  }
}

template <typename T>
T RandomUniform() {
  static thread_local std::mt19937 generator;
  return static_cast<T>(generator()) / static_cast<float>(UINT32_MAX);
}

template <typename T>
Vector3D<T> RandomUnitVector() {
  while (true) {
    Vector3D<T> out = {RandomUniform<T>() * 2 - 1, RandomUniform<T>() * 2 - 1,
                       RandomUniform<T>() * 2 - 1};

    if (Abs2(out) < 1 || Abs2(out) > 0.01) {
      return Norm(out);
    }
  }
}

template <typename T>
Vector3D<T> ChangeBasis(Vector3D<T> src, Vector3D<T> ex, Vector3D<T> ey,
                        Vector3D<T> ez) {
  return src.x * ex + src.y * ey + src.z * ez;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, Vector3D<T> v) {
  out << v.x << " " << v.y << " " << v.z;
  return out;
}

template <typename T>
struct Ray {
  Vector3D<T> point, direction;
  size_t lifetime{0};
};

}  // namespace math3d

#endif
