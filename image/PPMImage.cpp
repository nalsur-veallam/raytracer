#include <vector>
#include <fstream>
#include <iostream>
#include <assert.h>
#include "PPMImage.hpp"

namespace image {

class PPMImage: public IImage {
 public:
  PPMImage(size_t w, size_t h):
        w_(w), h_(h), data_(w, std::vector<Color>(h, Color::Default())) {
  }

  void Set(size_t x, size_t y, Color c) {
    assert(0 <= x && x < w_);
    assert(0 <= y && y < h_);
    data_[x][y] = c;
  }

  size_t Width() const {
    return w_;
  }

  size_t Height() const {
    return h_;
  }

  void Save(const std::string filename) {
    std::ofstream fout(filename);

    fout << "P3" << "\n";
    fout << w_ << " " << h_ << "\n";
    fout << 255 << "\n";
    for (int y = 0; y < h_; ++y) {
      for (int x = 0; x < w_; ++x) {
        PrintPixel(fout, data_[x][y]);
      }
    }

    fout << std::flush;

  }

 private:
  void PrintPixel(std::ostream& out, Color color) {
    out << (int)(color.r * 255) << " ";
    out << (int)(color.g * 255) << " ";
    out << (int)(color.b * 255) << "\n";
  }
  size_t w_, h_;
  std::vector<std::vector<Color>> data_;
};

IImagePtr MakePPMImage(size_t w, size_t h) {
  return std::make_shared<PPMImage>(w, h); // TODO: localization
}

}
