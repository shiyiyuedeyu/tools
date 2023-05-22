#include <atomic>    // std::atomic
#include <iostream>  // std::cout
#include <thread>    // std::thread

std::atomic<int> v = 0;

void plus() {
  for (int i = 0; i < 10000; ++i) {
    // ++v, ++使用了默认的内存顺序
    v.fetch_add(1, std::memory_order_relaxed)
  }
}

int main() {
  std::thread t1(plus);
  std::thread t2(plus);
  t1.join();
  t2.join();
  std::cout << "v: " << std::endl;
  
  return 0;
}
