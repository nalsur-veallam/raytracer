#ifndef RAYTRACER_IIMAGE_HPP
#define RAYTRACER_IIMAGE_HPP

#include <memory>
#include <cstddef>
#include <string>
#include <iostream>
#include "../raytracer/Color.hpp" // TODO: fix

namespace image {

class IImage {
 public:
  virtual void Set(size_t x, size_t y, Color c) = 0;
  virtual size_t Width() const = 0;
  virtual size_t Height() const = 0;
  virtual void Save(const std::string filename) = 0;
};

using IImagePtr = std::shared_ptr<IImage>;

}

#endif RAYTRACER_IIMAGE_HPP
