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

    Image8bit(int rows, int cols) : Mat(rows, cols, CV_8UC1) { }

    /**
     * PARAM m: Mat used to seed this Image8bit. Must be of type CV_8UC1,
     *      i.e. an 8-bit grayscale image.
     * PARAM copyData: if True, copy the pixel data stored in m into this object.
     *      If False, share the data between the two objects, such that a change in one
     *      results in a change in the other.
     */
    Image8bit(const cv::Mat &m, bool copyData) : Mat( copyData ? m.clone() : m ) {
        assert(m.type() == CV_8UC1);
    }

    /**
     * Overloads square brackets to work as a getter.
     */
    uint8_t pixelAt(int row, int col)  const{
        return this->at<uint8_t>(row, col);
    }

    /**
     * Overloads square brackets to work as a setter.
     */
    uint8_t &pixelAt(int row, int col)  {
        return this->at<uint8_t>(row, col);
    }

};


#endif //OBSTACLE_AVOIDANCE_IMAGE8BIT_H
