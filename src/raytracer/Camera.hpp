#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#include <iostream>
#include "../image/IImage.hpp"
#include "../math3d/Vector3D.hpp"
#include "../threadpool/ThreadPool.hpp"
#include "Scene.hpp"
namespace camera {

template <typename CoordType>
struct CameraParameters {
  math3d::Vector3D<CoordType> position;
  math3d::Vector3D<CoordType> up_direction;
  math3d::Vector3D<CoordType> direction;
  CoordType w_angle, h_angle;
  Scene<CoordType>* scene;
};

class ChunkCounter {
 public:
  ChunkCounter() = default;

  void AddChunk();
  void DoneChunk();

 private:
  std::mutex mutex_;
  size_t max_chunks_{0}, done_chunks_{0};
};

template <typename CoordType>
class Camera {
 public:
  explicit Camera(CameraParameters<CoordType> parameters)
      : parameters_(parameters) {
    parameters_.direction = math3d::Norm(parameters_.direction);
    parameters_.up_direction = math3d::Norm(parameters_.up_direction);
    right_direction_ =
        math3d::Norm(parameters_.direction % parameters_.up_direction);
  }

  image::IImagePtr TakePhoto(image::IImagePtr film, size_t chunk_w = 100,
                             size_t chunk_h = 100, size_t n_workers = 16) {
    auto thread_pool = multithreading::MakeThreadPool(n_workers);
    ChunkCounter counter;
    for (size_t chunk_y = 0; chunk_y < film->Height(); chunk_y += chunk_h) {
      for (size_t chunk_x = 0; chunk_x < film->Width(); chunk_x += chunk_w) {
        counter.AddChunk();
        thread_pool->SubmitTask(
            [chunk_x, chunk_y, chunk_w, chunk_h, &film, &counter, this]() {
              for (size_t x = chunk_x;
                   x < std::min(chunk_x + chunk_w, film->Width()); ++x) {
                for (size_t y = chunk_y;
                     y < std::min(chunk_y + chunk_h, film->Height()); ++y) {
                  ProcessPixel(film, x, y);
                }
              }
              counter.DoneChunk();
            });
      }
    }
    thread_pool->Start();
    return film;
  }

 private:
  void ProcessPixel(image::IImagePtr film, size_t x, size_t y) {
    CoordType x_angle = ((static_cast<CoordType>(x) -
                          static_cast<CoordType>(film->Width()) / 2) *
                         parameters_.w_angle) /
                        film->Width();
    CoordType y_angle = ((static_cast<CoordType>(y) -
                          static_cast<CoordType>(film->Height()) / 2) *
                         parameters_.h_angle) /
                        film->Height();

    math3d::Vector3D<CoordType> ray_direction =
        cos(y_angle) * (cos(x_angle) * parameters_.direction +
                        sin(x_angle) * right_direction_) +
        sin(y_angle) * parameters_.up_direction;

    Color color = parameters_.scene->Trace(
        math3d::Ray<CoordType>{parameters_.position, ray_direction});
    film->Set(x, film->Height() - 1 - y, color);
  }

 private:
  CameraParameters<CoordType> parameters_;
  math3d::Vector3D<CoordType> right_direction_;
};

}  // namespace camera

#endif
