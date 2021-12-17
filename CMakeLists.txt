cmake_minimum_required(VERSION 3.20)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(raytracer src/main.cpp src/raytracer/Scene.hpp src/math3d/Vector3D.hpp src/raytracer/Color.cpp src/raytracer/Color.hpp src/raytracer/objects/IObject.hpp src/raytracer/objects/Sphere.hpp src/image/IImage.hpp src/image/PPMImage.cpp src/image/PPMImage.hpp src/raytracer/Camera.hpp src/raytracer/Plain.hpp src/raytracer/surfaces/ISurface.hpp src/raytracer/Traceable.hpp src/raytracer/surfaces/Phong.hpp)
