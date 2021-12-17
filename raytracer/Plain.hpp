#ifndef RAYTRACER_PLAIN_HPP
#define RAYTRACER_PLAIN_HPP

#include "IObject.hpp"

namespace objects {

template <typename CoordType>
class Plain : public objects::IObject<CoordType> {
 public:
  Plain(math::Vector3D<CoordType> norm, math::Vector3D<CoordType> point):
      norm_(norm), point_(point) {

  }
  std::optional<CoordType> Intersects(math::Ray<CoordType> ray) {
    CoordType dist = ((point_ - ray.point) * norm_) / (ray.direction * norm_);
    if (dist > 0) {
      return dist;
    } else {
      return std::nullopt;
    }
  }

  virtual Color IntersectColor(math::Ray<CoordType> ray) {
    auto intersection = Intersects(ray);
    assert(intersection.has_value());  // TODO: rise error

    math::Vector3D<CoordType> hit =
        ray.point + math::Norm(ray.direction) * intersection.value();

    int x = static_cast<int>(std::floor(hit.x));
    int z = static_cast<int>(std::floor(hit.z));

    double intensity = static_cast<double>((abs(x % 2) + abs(z % 2)) % 2);
    intensity *= pow(ray.direction * norm_, 2);
    return {intensity, intensity, intensity};
  }

 private:
  math::Vector3D<CoordType> norm_;
  math::Vector3D<CoordType> point_;
};

}

#endif RAYTRACER_PLAIN_HPP
