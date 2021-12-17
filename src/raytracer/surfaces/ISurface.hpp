#ifndef RAYTRACER_ISURFACE_HPP
#define RAYTRACER_ISURFACE_HPP

#include "../../math3d/Vector3D.hpp"
#include "../Traceable.hpp"

namespace surfaces {

template <typename CoordType>
class ISurface {
 public:
  virtual Color GetColor(
      math3d::Ray<CoordType> ray, math3d::Vector3D<CoordType> norm,
      math3d::Vector3D<CoordType> hit) {  // TODO: better defaults
    auto intensity = pow(ray.direction * norm, 2);
    return {intensity, intensity, intensity};
  }
};

template <typename CoordType>
using ISurfacePtr = std::shared_ptr<ISurface<CoordType>>;

}  // namespace objects

#endif
