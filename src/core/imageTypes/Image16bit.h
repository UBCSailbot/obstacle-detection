//
// Created by paul on 12/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_IMAGE16BIT_H
#define OBSTACLE_AVOIDANCE_IMAGE16BIT_H


#include <opencv2/core/core.hpp>

/**
 * A convenience class to distinguish 16-bit images from 8-bit images.
 */
class Image16bit : public cv::Mat {

public:

    using cv::Mat::Mat; // TODO: Determine whether this is useful

    Image16bit() : Mat() {}
    Image16bit(int rows, int cols) : Mat(rows, cols, CV_16UC1) { }
    Image16bit(int rows, int cols, int type) : Mat(rows, cols, type) {}
    Image16bit(const cv::Mat &m) : Mat(m) {}

};


#endif //OBSTACLE_AVOIDANCE_IMAGE16BIT_H
