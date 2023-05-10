#pragma once

#include <atomic>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

template<typename T>
class CycleQueue{
 public:
  // init size must > 1
  explicit CycleQueue(int size = 1000) noexcept :
    c_size(size), c_front(0), c_rear(0) {
    c_data = new T[c_size];  
  }
  
  ~CycleQueue() {
    delete[] c_data;
  }
  
  bool isEmpty() {
    return c_front == c_rear;
  }
  
  bool isFull() {
    return c_front == (c_rear + 1) % c_size;
  }
  
  void push(T ele) {
    if (isFull()) {
      pop();
    }
    c_data[c_rear] = ele;
    c_rear = (c_rear + 1) % c_size;
  }
  
  T pop() {
    if (isEmpty()) {
      return T();
    }
    T tmp = c_data[c_front];
    c_front = (c_front + 1) % c_size;
    return tmp;
  }
 private:
  int c_size;
  std::atomic<int> c_front;
  std::atomic<int> c_rear;
  T* c_data;
};




