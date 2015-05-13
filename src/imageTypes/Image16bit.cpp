//
// Created by paul on 12/05/15.
//

#include "Image16bit.h"

Image16bit Image16bit::fromMat(cv::Mat src) {
    Image16bit image = Image16bit(src.rows, src.cols, src.type());
    for(int x = 0; x < src.cols; x++) {
        for(int y=0; y < src.rows; y++) {
            image.at<uint8_t>(y, x) = src.at<uint8_t>(y, x);
        }
    }
    return image;
}