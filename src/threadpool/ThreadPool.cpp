#include <deque>
#include <mutex>
#include <thread>
#include <atomic>
#include "ThreadPool.hpp"

namespace multithreading {

class ThreadPoolQueue {
 public:
  void Push(Task task) {
    std::lock_guard<std::mutex> lock(mutex_);
    tasks_.push_back(std::move(task));
  }

  std::optional<Task> Pop() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (tasks_.empty()) {
      return std::nullopt;
    }
    auto out = tasks_.front();
    tasks_.pop_front();
    return std::move(out);
  }

 private:
  std::deque<Task> tasks_;
  std::mutex mutex_;
};

struct ThreadPoolIsNotCoolEnough : public std::exception {
  const char* what() const throw() {
    return "This thread pool is not cool enough to submit task after run";
  }
};

// you can not submit after run
class ThreadPool : public IThreadPool {
 public:
  explicit ThreadPool(size_t n_workers)
      : n_workers_(n_workers), in_progress_(false) {
  }

  void SubmitTask(Task task) {
    queue_.Push(std::move(task));
    if (in_progress_.load()) {
      throw ThreadPoolIsNotCoolEnough();
    }
  };
  void Start() {
    std::vector<std::thread> workers;
    for (int worker_id = 0; worker_id < n_workers_; ++worker_id) {
      workers.emplace_back([&]() {
        while (true) {
          auto task = queue_.Pop();
          if (task.has_value()) {
            task.value()();
          } else {
            break;
          }
        }
      });
    }
    for (auto& worker : workers) {
      worker.join();
    }
  };

 private:
  std::atomic<bool> in_progress_;
  ThreadPoolQueue queue_;
  size_t n_workers_;
};

IThreadPoolPtr MakeThreadPool(size_t n_workers) {
  return std::make_shared<ThreadPool>(n_workers);
}

}  // namespace multithreading
