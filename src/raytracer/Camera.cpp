#include <mutex>
#include "Camera.hpp"

void camera::ChunkCounter::AddChunk() {
  std::lock_guard<std::mutex> lock(mutex_);
  ++max_chunks_;
}
void camera::ChunkCounter::DoneChunk() {
  std::lock_guard<std::mutex> lock(mutex_);
  ++done_chunks_;
  std::cout << done_chunks_ << "/" << max_chunks_ << std::endl;
}
