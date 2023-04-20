#include <chrono>
#include <iostream>

using namespace std;

int main() {
  
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  // do something
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  std::cout << "Time Cost: " << time_span.count() * 1000 << "ms";
  
  return 0;
}
