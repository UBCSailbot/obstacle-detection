//
// Created by denis on 09/06/16.
//

#include <opencv2/core/types_c.h>
#include <ml.h>
#include <highgui.h>
#include "Compressor.h"

//This was necessary for CV_IMWRITE_PNG_COMPRESSION to be found
using namespace cv;

std::vector<uchar> Compressor::imgToBuff(cv::Mat img, int compressionLevel) {
    std::vector<uchar> buff;//buffer for coding
    std::vector<int> param = std::vector<int>(2);

    param[0] = CV_IMWRITE_PNG_COMPRESSION;

    param[1] = compressionLevel;
    cv::imencode(".png", img, buff, param);
    return buff;
}

