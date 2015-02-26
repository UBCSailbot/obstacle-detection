#ifndef BITGRAY_H_
#define BITGRAY_H_

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdint>

cv::Mat generate_16bit_img();
void show_16bit_img(const cv::Mat&);
void save_16bit_img(const std::string&, const cv::Mat&, int);
cv::Mat load_16bit_img(const std::string&);
void test_16bitgray();

int max_pixel_val(const cv::Mat&);

#endif /* 16BITGRAY_H_ */
