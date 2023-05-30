// 读取图片，imread会将图片内容解码成yuv或者bgr存放在Mat对象
cv::Mat src_mat = cv::imread("test.jpg");
// 获取图片固定区域的内容
cv::Mat dst_mat = src_mat(cv::Rect(100, 100, 1600, 900));
// 对固定区域的内容重新进行jpg编码，生成jpg图片，存入jpg_buff
std::vector<uchar> jpg_buff;
bool ret = cv::imencode(".jpg", dst_mat, jpg_buff);
FILE *file = fopen("2.jpg", "wb");
if (file != nullptr) {
  // 将jpg图片写入内存
  fwrite(jpg_buff.data(), 1, jpg_buff.size(), file);
  fclose(file);
}
/*
  从内存中加载图片：
  1、从内存直接加载；
  2、通过cv::imdecode接口将图片解码成cv::Mat
*/

FILE *file = fopen("test.jpg", "rb");
uchar *mem_pic = nullptr;
long size = 0;
if (file != nullptr) {
  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);
  mem_pic = new uchar[size];
  fread(mem_pic, 1, size, file);
  fclose(file);
}

cv::_InputArray pic_arr(mem_pic, size);
cv::Mat src_mat = cv::imdecode(pic_arr, CV_LOAD_IMAGE_COLOR);
cv::Mat dst_src = src_mat(cv::Rect(100, 100, 1600, 900));
std::vector<uchar> pic_buff;
bool ret = cv::imencode(".jpg", dst_src, pic_buff);
file = fopen("3.jpg", "wb");
if (file != nullptr) {
  fwrite(pic_buff.data(), 1, pic_buff.size(), file);
  fclose(file);
}
/*
  cv::_Array还可以使用std::vector代替
*/
FILE *file = fopen("1.jpg", "rb");
uchar *mem_pic = nullptr;
long size = 0;
if (file != nullptr) {
  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);
  mem_pic = new uchar[size];
  fread(mem_pic, 1, size, file);
  fclose(file);
}

std::vector<uchar> pic_vec(mem_pic, mem_pic + size);
cv::Mat src_mat = cv::imdecode(pic_vec, CV_LOAD_IMAGE_COLOR);
cv::Mat dst_src = src_mat(cv::Rect(200, 200, 400, 225));
std::vector<uchar> pic_buff;
bool ret = cv::imdecode(".jpg", dst_src, pic_buff);
file = fopen("3.jpg", "wb");
if (file != nullptr) {
  fwrite(pic_buff.data(), 1, pic_buff.size(), file);
  fclose(file);
}
