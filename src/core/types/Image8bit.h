//
// Created by paul on 12/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_IMAGE8BIT_H
#define OBSTACLE_AVOIDANCE_IMAGE8BIT_H


#include <opencv2/core/core.hpp>

#include "exceptions/IncorrectImageTypeException.h"


/**
 * A convenience class to distinguish 16-bit images from 8-bit images.
 */
class Image8bit: public cv::Mat {
    
  public:

    Image8bit();

    Image8bit(int rows, int cols);

    /**
     * Create an Image8bit whose pixel data is copied from the
     *  area of memory pointed to by the given pointer.
     * 
     * IMPORTANT - since this constructor copies rows * cols bytes
     *  from the part of memory pointed to by data, it assumes that
     *  some other part of the program will make sure that memory is
     *  readable, and that that memory will be properly deallocated
     *  elsewhere in the code at some future point in time.
     * 
     * @param rows - number of rows in the image
     * @param cols - number of columns in the image
     * @param data - pointer to bytes that encode an image.
     */
    Image8bit(int rows, int cols, void *data);

    /**
     * Make an Image8bit that is a copy of the given Mat.
     *
     * @param m - Mat that will be copied into this Image8bit.
     *  Must be of type CV_8UC1, i.e. an 8bit grayscale image.
     * @param copyData - if True, copy the pixel data stored in m into
     *  the new Image8bit being created. If False, share the data
     *  between the two objects, such that a change in one results
     *  in a change in the other.
     */
    Image8bit(const cv::Mat &m, bool copyData);

    /**
     * Gets the specified pixel value from this image.
     *
     * @param row - the row of the image containing the desired pixel
     * @param col - the column of the image containing the desired pixel
     *
     * @return the value of the desired pixel.
     */
    uint8_t pixelAt(int row, int col) const;

    /**
     * Returns an r-value that can be used to easily set the value
     *  of a particular pixel in the image.
     *
     * E.g. mat.pixelAt(row, col) = 128
     *    // sets the value of the pixel at (row, col) to 128
     *
     * @param row - the row of the image containing the desired pixel
     * @param col - the column of the image containing the desired pixel
     *
     * @return the value of the desired pixel.
     */
    uint8_t &pixelAt(int row, int col);

    /**
      * Force the given cv::Mat to become of type CV_8UC1.
      *
      * WARNING: Does not check whether or not it makes sense to interpret
      *  the given Mat as an 8-bit image. If you use this function without
      *  knowing what you're doing, you may get undefined behavior.
      */
    static void forceConversion(cv::Mat &mat);

};

bool operator==(const Image8bit &lhs, const Image8bit &rhs);


#endif //OBSTACLE_AVOIDANCE_IMAGE8BIT_H
