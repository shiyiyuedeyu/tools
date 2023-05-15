#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main() {
  std::string pattern{"\\.jpg$"};
  std::string pattern2{"\\.png$"};

  std::regex re(pattern);
  std::regex re2(pattern2);

  std::string tmp = "test.png";
  bool ret = std::regex_search(tmp, re);
  bool ret2 = std::regex_search(tmp, re2);
  if (ret) {
    std::cout << "this is a jpg";
  }
  if (ret2) {
    std::cout << "this is a png";
  }

  return 0;
}
