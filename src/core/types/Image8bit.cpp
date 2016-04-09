#include "Image8bit.h"

Image8bit::Image8bit() : cv::Mat() {
    forceConversion(*this);
}

Image8bit::Image8bit(int rows, int cols) : Mat(rows, cols, CV_8UC1) { }

Image8bit::Image8bit(int rows, int cols, void *data) :
        Mat(rows, cols, CV_8UC1)
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
    cv::Mat container(rows, cols, CV_8UC1, data);
    container.copyTo(*this);
}

Image8bit::Image8bit(const cv::Mat &m, bool copyData) : Mat(copyData ? m.clone() : m) {
    if (m.type() != CV_8UC1) {
        throw IncorrectImageTypeException("parameter m is of wrong type");
    }
}

uint8_t Image8bit::pixelAt(int row, int col) const {
    return this->at<uint8_t>(row, col);
}

uint8_t &Image8bit::pixelAt(int row, int col) {
    return this->at<uint8_t>(row, col);
}

void Image8bit::forceConversion(cv::Mat &mat) {
    mat.flags = mat.flags & (1 << 12);
    mat.flags += CV_8UC1;
}

bool operator==(const Image8bit &lhs, const Image8bit &rhs) {
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
