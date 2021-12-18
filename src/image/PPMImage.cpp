#include <vector>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <mutex>
#include <shared_mutex>
#include "PPMImage.hpp"

namespace image {

class PPMImage : public IImage {
 public:
  PPMImage(size_t w, size_t h)
      : w_(w), h_(h), data_(w, std::vector<Color>(h, Color{0, 1, 0})) {
  }

  void Set(size_t x, size_t y, Color c) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    assert(0 <= x && x < w_);
    assert(0 <= y && y < h_);
    data_[x][y] = c;
  }

  size_t Width() const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return w_;
  }

  size_t Height() const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return h_;
  }

  void Save(const std::string filename) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    std::ofstream fout(filename);

    fout << "P3"
         << "\n";
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
    PrintSubPixel(out, color.r);
    PrintSubPixel(out, color.g);
    PrintSubPixel(out, color.b);
  }
  void inline PrintSubPixel(std::ostream& out, double sub_color) {
    out << std::max(0, std::min(255, (int)(sub_color * 255))) << " ";
  }

 private:
  mutable std::shared_mutex mutex_;
  size_t w_, h_;
  std::vector<std::vector<Color>> data_;
};

IImagePtr MakePPMImage(size_t w, size_t h) {
  return std::make_shared<PPMImage>(w, h);
}

}  // namespace image
