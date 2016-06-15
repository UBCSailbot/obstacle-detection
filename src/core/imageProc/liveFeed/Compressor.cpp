#include <opencv2/core/types_c.h>
#include <opencv2/highgui/highgui.hpp>
#include "Compressor.h"

std::vector<uchar> Compressor::imgToBuff(cv::Mat img, int compressionLevel) {
    std::vector<uchar> buff;//buffer for coding
    std::vector<int> param(2);

    param[0] = CV_IMWRITE_PNG_COMPRESSION;

    param[1] = compressionLevel;
    cv::imencode(".png", img, buff, param);
    return buff;
}

