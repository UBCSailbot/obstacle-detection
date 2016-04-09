#include "Image16bit.h"

Image16bit::Image16bit() : cv::Mat() {
    forceConversion(*this);
}

Image16bit::Image16bit(int rows, int cols) : Mat(rows, cols, CV_16UC1) { }

Image16bit::Image16bit(int rows, int cols, void *data) :
        Mat(rows, cols, CV_16UC1)
{
    /*
     * We use an intermediary "container" Mat because the Mat constructor,
     *  which takes as input a pointer to an image blob, creates
     *  a Mat that does not handle its own memory deallocation.
     *  We do not want that kind of a Mat to be returned from this
     *  function.
     * However, using the Mat::copyTo function creates a Mat which does
     *  take care of its own memory, so a Mat created in this way
     *  is safe to return.
     */
    cv::Mat container(rows, cols, CV_16UC1, data);
    container.copyTo(*this);
}

Image16bit::Image16bit(const cv::Mat &m, bool copyData) : Mat(copyData ? m.clone() : m) {
    if (m.type() != CV_16UC1) {
        throw IncorrectImageTypeException("Expected type of cv::Mat to be CV_16UC1.");
    }
}

uint16_t Image16bit::pixelAt(int row, int col) const {
    return this->at<uint16_t>(row, col);
}

uint16_t &Image16bit::pixelAt(int row, int col) {
    return this->at<uint16_t>(row, col);
}

void Image16bit::forceConversion(cv::Mat &mat) {
    mat.flags = mat.flags & (1 << 12);
    mat.flags += CV_16UC1;
}

bool operator==(const Image16bit &lhs, const Image16bit &rhs) {
    if (lhs.rows != rhs.rows || lhs.cols != rhs.cols) {
        return false;
    }

    for (int row = 0; row < lhs.rows; row++) {
        for (int col = 0; col < lhs.cols; col++) {
            if (lhs.pixelAt(row, col) != rhs.pixelAt(row, col)) {
                return false;
            }
        }
    }

    return true;
}
