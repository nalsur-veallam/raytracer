#include <memory>
#include <mutex>
#include <deque>

#include "raytracer/Scene.hpp"
#include "raytracer/objects/Sphere.hpp"
#include "raytracer/Camera.hpp"

#include "image/PPMImage.hpp"
#include "raytracer/surfaces/Plain.hpp"
#include "raytracer/surfaces/Phong.hpp"
#include "threadpool/ThreadPool.hpp"

using Vector3Dd = math3d::Vector3D<double>;

int main() {
  Scene<double> scene;

  scene.AddObject(
      std::make_shared<objects::Sphere<double>>(Vector3Dd{2.0, 0, -10}, 1)
          ->WithSurface(surfaces::MakeGlowingSurface<double>(10, &scene)));

  scene.AddObject(
      std::make_shared<objects::Sphere<double>>(Vector3Dd{-2.0, 0, -10}, 1)
          ->WithSurface(surfaces::MakeOpaqueSurface<double>(1, 1, &scene, 1000)));

  scene.AddObject(std::make_shared<objects::Plain<double>>(
      Vector3Dd{0, 1, 0}, Vector3Dd{0, -3, 0}));

  auto camera =
      camera::Camera(camera::CameraParameters<double>{{0, 0, 0},
                                                      {0, 1, 0},
                                                      {0, 0, -1},
                                                      M_PI / 3,
                                                      M_PI / 3 * 1080 / 1080,
                                                      &scene});

  camera.TakePhoto(image::MakePPMImage(1080, 1080))->Save("test.ppm");
}
