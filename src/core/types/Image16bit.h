//
// Created by paul on 12/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_IMAGE16BIT_H
#define OBSTACLE_AVOIDANCE_IMAGE16BIT_H


#include <opencv2/core/core.hpp>
#include "exceptions/IncorrectImageTypeException.h"

/**
 * A convenience class to distinguish 16-bit images from 8-bit images.
 */
class Image16bit : public cv::Mat {

public:

    Image16bit() : cv::Mat() {
        forceConversion(*this);
    }

    Image16bit(int rows, int cols) : Mat(rows, cols, CV_16UC1) { }
    Image16bit(int rows, int cols, void* data) : Mat(rows, cols, CV_16UC1, data) {}

    /**
     * PARAM m: Mat used to seed this Image16bit. Must be of type CV_16UC1,
     *      i.e. an 16-bit grayscale image.
     * PARAM copyData: if True, copy the pixel data stored in m into this object.
     *      If False, share the data between the two objects, such that a change in one
     *      results in a change in the other.
     */
    Image16bit(const cv::Mat &m, bool copyData) : Mat( copyData ? m.clone() : m ) {
        if(m.type() != CV_16UC1){
            throw IncorrectImageTypeException("parameter m is of wrong type");
        }
    }

    /**
     * Overloads square brackets to work as a getter.
     */
    uint16_t pixelAt(int row, int col)  const{
        return this->at<uint16_t>(row, col);
    }

    /**
     * Overloads square brackets to work as a setter.
     */
    uint16_t & pixelAt(int row, int col)  {
        return this->at<uint16_t>(row, col);
    }

    /**
     * Force the given cv::Mat to become of type CV_16UC1.
     *
     * CAUTION: always sets the flag to CV_16UC1 even if mat is malformed.
     */
    static void forceConversion(cv::Mat &mat) {
        mat.flags = mat.flags & (1 << 12);
        mat.flags += CV_16UC1;
    }

};


#endif //OBSTACLE_AVOIDANCE_IMAGE16BIT_H
