#include <iostream>
#include <memory>

#include "Scene.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"

#include "../image/PPMImage.hpp"  // TODO: fix
#include "Plain.hpp"

int main() {
  Scene<double> scene;
  scene.AddObject(std::make_shared<objects::Sphere<double>>(
      math::Vector3D<double>{0, 0, -10}, 1));
  scene.AddObject(std::make_shared<objects::Sphere<double>>(
      math::Vector3D<double>{1, 2, -10}, 1));

  scene.AddObject(std::make_shared<objects::Plain<double>>(
      math::Vector3D<double>{0, 1, 0}, math::Vector3D<double>{0, -3, 0}));

  auto camera =
      camera::Camera(camera::CameraParameters<double>{{0, 0, 0},
                                                      {0, 2, 0},
                                                      {0, 0, -1},
                                                      M_PI / 3,
                                                      M_PI / 3 * 1080 / 1080,
                                                      &scene});

  camera.TakePhoto(image::MakePPMImage(1920, 1080))->Save("test.ppm");
}
