#ifndef RAYTRACER_IOBJECT_HPP
#define RAYTRACER_IOBJECT_HPP

#include <optional>
#include "../../math3d/Vector3D.hpp"
#include "../surfaces/ISurface.hpp"

namespace objects {

template <typename CoordType>
class IObject : public std::enable_shared_from_this<IObject<CoordType>> {
  using IObjectPtr = std::shared_ptr<IObject<CoordType>>;

 public:
  virtual std::optional<CoordType> Intersects(math3d::Ray<CoordType> ray) = 0;
  virtual Color IntersectColor(math3d::Ray<CoordType> ray) = 0;

  surfaces::ISurfacePtr<CoordType> GetSurface() {
    return surface_;
  }

  IObject() {
    surface_ = std::make_shared<surfaces::ISurface<CoordType>>();
  }

  IObjectPtr WithSurface(surfaces::ISurfacePtr<CoordType> surface) {
    surface_ = surface;
    return this->shared_from_this();
  }

 private:
  surfaces::ISurfacePtr<CoordType> surface_;
};

template <typename CoordType>
using IObjectPtr = std::shared_ptr<IObject<CoordType>>;

}  // namespace objects

#endif
