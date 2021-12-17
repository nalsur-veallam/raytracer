#ifndef RAYTRACER_TRACEABLE_HPP
#define RAYTRACER_TRACEABLE_HPP

#include "Color.hpp"
#include "../math3d/Vector3D.hpp"

template<typename CoordType>
class Traceable {
 public:
  virtual Color Trace(math3d::Ray<CoordType> ray) = 0;
};

#endif
