#include <memory>

#include "raytracer/Scene.hpp"
#include "raytracer/objects/Sphere.hpp"
#include "raytracer/Camera.hpp"

#include "image/PPMImage.hpp"
#include "raytracer/Plain.hpp"
#include "raytracer/surfaces/Phong.hpp"

int main() {
  Scene<double> scene;
  scene.AddObject(std::make_shared<objects::Sphere<double>>(
                      math3d::Vector3D<double>{2.0, 0, -10}, 1)
                      ->WithSurface(std::make_shared<surfaces::Phong<double>>(
                          10.0, 0.0, 0.0, &scene, 1000)));

  scene.AddObject(std::make_shared<objects::Sphere<double>>(
                      math3d::Vector3D<double>{-2.0, 0, -10}, 1)
                      ->WithSurface(std::make_shared<surfaces::Phong<double>>(
                          0.0, 1, 1, &scene, 1000)));

  scene.AddObject(std::make_shared<objects::Plain<double>>(
      math3d::Vector3D<double>{0, 1, 0}, math3d::Vector3D<double>{0, -3, 0}));

  auto camera =
      camera::Camera(camera::CameraParameters<double>{{0, 0, 0},
                                                      {0, 1, 0},
                                                      {0, 0, -1},
                                                      M_PI / 3,
                                                      M_PI / 3 * 1080 / 1080,
                                                      &scene});

  camera.TakePhoto(image::MakePPMImage(1000, 1000))->Save("test.ppm");
}
