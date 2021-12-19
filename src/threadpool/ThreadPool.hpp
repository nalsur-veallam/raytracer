#ifndef RAYTRACER_THREADPOOL_HPP
#define RAYTRACER_THREADPOOL_HPP

#include <cstdlib>
#include <functional>
#include <memory>
#include <optional>
namespace multithreading {

struct Rectangle {
  size_t x0, y0, x1, y1;
};

using Task = std::function<void()>;

class IThreadPool {
 public:
  virtual void SubmitTask(Task) = 0;
  virtual void Start() = 0;
};

using IThreadPoolPtr = std::shared_ptr<IThreadPool>;

IThreadPoolPtr MakeThreadPool(size_t n_workers);

}  // namespace multithreading

#endif
