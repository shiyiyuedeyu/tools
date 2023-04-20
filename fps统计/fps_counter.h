#pragma once

#include <chrono>
namespace fps {
  
class FpsCounter {
 public:
  FpsCounter() { start_time_ = std::chrono::high_resolution_clock::now(); }
  
  void AddOne() { frame_count_++; };
  
  fload Compute() {
    const auto time_now = std::chrono::high_resolution_clock::now();
    auto dur_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                   time_now - start_time_).count();
    if (0 == dur_ms) {
      return 0;
    }
    return static_cast<float>(frame_count_) / dur_ms * 1000;
  }
  
  size_t FrameCount() const { return frame_count_; }
  
  float Update(size_t frame_count, std::chrono::high_resolution_clock::time_point start_time) {
    auto fps = Compute();
    frame_count_ = frame_count;
    start_time_ = start_time;
    return fps;
  }
  
 private:
  std::chrono::high_resolution_clock::time_point start_time_;
  size_t frame_count_ = 0;

};
  
}  // namespace fps
