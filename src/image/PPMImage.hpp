#ifndef RAYTRACER_PPMIMAGE_HPP
#define RAYTRACER_PPMIMAGE_HPP

#include "IImage.hpp"

namespace image {

IImagePtr MakePPMImage(size_t w, size_t h);

}

#endif
