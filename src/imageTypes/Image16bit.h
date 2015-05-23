//
// Created by paul on 12/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_IMAGE16BIT_H
#define OBSTACLE_AVOIDANCE_IMAGE16BIT_H


#include <opencv2/core/core.hpp>

class Image16bit : public cv::Mat {

public:
    Image16bit() : Mat() {}
    Image16bit(int rows, int cols) : Mat(rows, cols, CV_16UC1) { }

    using cv::Mat::Mat;

    Image16bit(int rows, int cols, int type) : Mat(rows, cols, type) {}

    static Image16bit fromMat(cv::Mat src);
};


#endif //OBSTACLE_AVOIDANCE_IMAGE16BIT_H
