#include <iostream>

#include "fps_counter.h"

namespace fps {

class Test {
 public:
  
  void Workloop() {
    while (true) {
      fps_counter_.AddOne();
      if (10 == fps_counter_.FrameCount()) {
        std::coout << "fps: " << fps_counter_.Update(0, std::chrono::high_resolution_clock::now());
      }
    }
  }
  
 private:
    pg::FpsCounter fps_counter_;
};
  
}  // namespace fps
