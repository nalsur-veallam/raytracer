#ifndef RAYTRACER_PHONG_HPP
#define RAYTRACER_PHONG_HPP

#include "ISurface.hpp"

namespace surfaces {

template <typename CoordType>
class Phong : public surfaces::ISurface<CoordType> {
 public:
  Phong(double ambient, double diffuse, double specular,
        Traceable<CoordType>* scene, size_t n_reflections)
      : ambient_(ambient),
        diffuse_(diffuse),
        specular_(specular),
        scene_(scene),
        n_reflections_(n_reflections) {
  }

  Color GetColor(math3d::Ray<CoordType> ray, math3d::Vector3D<CoordType> norm,
                 math3d::Vector3D<CoordType> hit) {
    Color ambient = {ambient_, ambient_, ambient_};

    if (ray.lifetime > 0) {
      return ambient;
    }

    auto ey = norm;
    auto ex = math3d::NormAndRotate90(ey);
    auto ez = ex % ey;

    Color diffuse{0, 0, 0};
    Color specular{0, 0, 0};

    if (n_reflections_ == 0) {
      return ambient;
    }

    for (size_t i = 0; i < n_reflections_; ++i) {
      auto random_unit = math3d::RandomUnitVector<CoordType>();
      random_unit.y = abs(random_unit.y);
      auto direction = ChangeBasis(random_unit, ex, ey, ez);
      Color intensity = scene_->Trace(math3d::Ray<CoordType>{
          hit + direction * 1e-4, direction, ray.lifetime + 1});

      auto specular_intensity =
          (ray.direction * (2. * (direction * norm) * norm - direction));
      if (specular_intensity < 0) {
        specular_intensity = 0;
      }
      diffuse = diffuse + intensity * abs(norm * direction);
      specular = specular + intensity * specular_intensity;
    }

    return ambient + diffuse * (diffuse_ / n_reflections_) +
           specular * (specular_ / n_reflections_);
  }

 private:
  double ambient_;
  double diffuse_;
  double specular_;
  Traceable<CoordType>* scene_;
  size_t n_reflections_;
};

template<typename CoordType>
ISurfacePtr<CoordType> MakeGlowingSurface(CoordType intensity, Traceable<CoordType>* scene) {
  return std::make_shared<Phong<CoordType>>(intensity, 0, 0, scene, 0);
}

template<typename CoordType>
ISurfacePtr<CoordType> MakeOpaqueSurface(CoordType opacity, CoordType gloss, Traceable<CoordType>* scene, size_t quality) {
  return std::make_shared<Phong<CoordType>>(0, opacity, gloss, scene, quality);
}

}  // namespace surfaces

#endif
