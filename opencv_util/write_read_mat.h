#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "opencv2/opencv.hpp"

namespace opencv_util {

/**
 * 保存mat头的关键信息
 */
struct MatHeader {
  // 行数
  int rows;
  // 列数
  int cols;
  // 类型
  int type;
};

/**
 * 以二进制文件来存储mat数据，读取这个函数存储的文件，需要用到下面的read函数
 * 
 */
void mat_write(std::string& filename, cv::Mat& src) {
  if (filename.empty()) {
    std::cout << "[psd opencv util::mat_write]" << "filename is empty!" << std::endl;
    return;
  }
  MatHeader mat_header{src.rows, src.cols, src.type()};

  std::ofstream out(filename, std::ios::binary);
  out.write((char *)&mat_header, sizeof(mat_header));
  out.write((char *)src.data, src.rows * src.cols * src.elemSize());

  out.flush();
  out.close();
}

/**
 * 读取mat文件
 * 
 */
cv::Mat mat_read(std::string& filename) {
  std::ifstream in(filename, std::ios::binary);

  MatHeader mat_header;
  in.read((char *)&mat_header, sizeof(mat_header));

  cv::Mat mat(mat_header.rows, mat_header.cols, mat_header.type);
  in.read((char *)mat.data, mat.rows * mat.cols * mat.elemSize());

  in.close();
  return mat;
}
}  // namespace opencv_util
