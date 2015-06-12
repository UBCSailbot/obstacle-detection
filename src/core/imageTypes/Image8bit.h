//
// Created by paul on 12/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_IMAGE8BIT_H
#define OBSTACLE_AVOIDANCE_IMAGE8BIT_H


#include <opencv2/core/core.hpp>

/**
 * A convenience class to distinguish 16-bit images from 8-bit images.
 */
class Image8bit : public cv::Mat {


public:

    using cv::Mat::Mat; // TODO: Determine whether this is useful

    Image8bit() : Mat() {}
    Image8bit(int rows, int cols) : Mat(rows, cols, CV_8UC1) { }
    Image8bit(int rows, int cols, int type) : Mat(rows, cols, type) { }
    Image8bit(const cv::Mat &m) : Mat(m) {}

};


#endif //OBSTACLE_AVOIDANCE_IMAGE8BIT_H
