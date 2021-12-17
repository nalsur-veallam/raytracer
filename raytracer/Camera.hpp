#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#include <iostream>
#include "../image/IImage.hpp"  // TODO: fix
#include "Vector3D.hpp"
#include "Scene.hpp"

namespace camera {

template <typename CoordType>
struct CameraParameters {
  math::Vector3D<CoordType> position;
  math::Vector3D<CoordType> up_direction;
  math::Vector3D<CoordType> direction;
  CoordType w_angle, h_angle;
  Scene<CoordType>* scene;
};

template <typename CoordType>
class Camera {
 public:
  Camera(CameraParameters<CoordType> parameters) : parameters_(parameters) {
  }

  image::IImagePtr TakePhoto(image::IImagePtr film) {
    auto direction = math::Norm(parameters_.direction);
    auto up_direction = math::Norm(parameters_.up_direction);
    auto right_direction =
        math::Norm(parameters_.direction % parameters_.up_direction);
    for (size_t y = 0; y < film->Height(); ++y) {
      for (size_t x = 0; x < film->Width(); ++x) {
        CoordType x_angle = ((static_cast<CoordType>(x) - static_cast<CoordType>(film->Width()) / 2) *
                             parameters_.w_angle) /
                            film->Width();
        CoordType y_angle = ((static_cast<CoordType>(y) - static_cast<CoordType>(film->Height()) / 2) *
                             parameters_.h_angle) /
                            film->Height();
        math::Vector3D<CoordType> ray_direction =
            cos(y_angle) *
                (cos(x_angle) * direction + sin(x_angle) * right_direction) +
            sin(y_angle) * up_direction;

        Color color = parameters_.scene->Trace(
            math::Ray<CoordType>{parameters_.position, ray_direction});
        film->Set(x, film->Height() - 1 - y, color);
      }
    }
    return film;
  }

 private:
  CameraParameters<CoordType> parameters_;
};

}  // namespace camera

#endif RAYTRACER_CAMERA_HPP
