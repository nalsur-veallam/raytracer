cmake_minimum_required(VERSION 3.20)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(raytracer raytracer/main.cpp raytracer/Scene.hpp raytracer/Vector3D.hpp raytracer/Color.cpp raytracer/Color.hpp raytracer/IObject.hpp raytracer/Sphere.hpp image/IImage.cpp image/IImage.hpp image/PPMImage.cpp image/PPMImage.hpp raytracer/Camera.cpp raytracer/Camera.hpp raytracer/Plain.hpp)
