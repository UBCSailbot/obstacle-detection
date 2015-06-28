//
// Created by paul on 16/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_IMAGEREADER_H
#define OBSTACLE_AVOIDANCE_IMAGEREADER_H

#include <string>

#include <opencv2/highgui/highgui.hpp>
#include <types/Image16bit.h>
#include <types/Image8bit.h>

class ImageReader {

public:

    static Image16bit read16bitImage(const std::string &filePath) {
        cv::Mat img = cv::imread(filePath, CV_LOAD_IMAGE_UNCHANGED);
        Image16bit::forceConversion(img);
        return Image16bit(img, false);
    }

    static Image8bit read8bitImage(const std::string &filePath) {
        cv::Mat img = cv::imread(filePath, CV_LOAD_IMAGE_UNCHANGED);
        Image8bit::forceConversion(img);
        return Image8bit(img, false);
    }


};


#endif //OBSTACLE_AVOIDANCE_IMAGEREADER_H
