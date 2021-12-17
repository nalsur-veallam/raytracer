#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include <assert.h>
#include "Vector3D.hpp"
#include "IObject.hpp"

namespace objects {

template <typename CoordType>
class Sphere : public IObject<CoordType> {
  using Vector3D = math::Vector3D<CoordType>;

 public:
  explicit Sphere(Vector3D position, CoordType radius)
      : position_(position),
        radius_(radius){

        };

  std::optional<CoordType> Intersects(math::Ray<CoordType> ray) {
    auto distance = Abs(position_ - ray.point);
    if (distance < radius_) {
      return {0};
    }

    auto cos = ray.direction * Norm(position_ - ray.point);
    auto discriminant =
        pow(distance * cos, 2) - pow(distance, 2) + pow(radius_, 2);
    if (discriminant < 0) {
      return std::nullopt;
    }

    return std::max((distance * cos) - sqrt(discriminant), CoordType{0});
  }

  virtual Color IntersectColor(math::Ray<CoordType> ray) {
    auto intersection = Intersects(ray);
    assert(intersection.has_value());  // TODO: rise error

    math::Vector3D<CoordType> hit =
        ray.point + math::Norm(ray.direction) * intersection.value();

    auto intensity = pow((position_ - hit) * Norm(ray.direction), 2);
    return {intensity, intensity, intensity};
  }

 private:
  Vector3D position_;
  CoordType radius_;
};

}  // namespace objects

#endif RAYTRACER_SPHERE_HPP
