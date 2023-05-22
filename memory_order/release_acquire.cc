/*
  release和acquire通常会配对使用，如果线程1里面写一个原子变量的操作A使用release，线程2里面读该原子变量的操作B使用
  acquire。如果线程2的B操作读到了线程1的A操作写入的值，那么线程1里面在A之前发生的所有内存写操作（包括原子写和非原子写，
  这里的所有内存指的是任意变量或者内存，不仅仅指该原子变量）对线程2都是可见的。这个关系是存在于对同一个原子变量分别
  使用了release和acquire的两个线程之间。其他线程观察到的线程1和线程2的执行顺序还是可能不一样的。
*/

#include <thread>
#include <atomic>
#include <cassert>
#include <string>

std::atomic<std::string*> ptr;
int data;

void producer() {
  std::string* p = new std::string("Hello");
  data = 42;
  ptr.store(p, std::memory_order_release);
}

void consumer() {
  std::string* p2;
  while (!(p2 = ptr.load(std::memory_order_acquire)));
  assert(*p2 == "Hello");  // 不可能失败
  assert(data == 42);  // 不可能失败
}

int main() {
  std::thread t1(producer);
  std::thread t2(consumer);
  t1.join();
  t2.join();
}
