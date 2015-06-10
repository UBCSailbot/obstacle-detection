//
// Created by paul on 25/05/15.
//

#include "Rescaling.h"

void Rescaling::rescale8bitWindow(const Image16bit &src, Image8bit &dst, const int &newMinPixelValue) {
    assert(dst.size == src.size);

    for (int row = 0; row < src.rows; row++) {
        for (int col = 0; col < src.cols; col++) {
            int scaledValue = src.at<uint16_t>(row, col) - newMinPixelValue;
            if (scaledValue > 255)
                scaledValue = 255;
            else if (scaledValue < 0)
                scaledValue = 0;
            dst.at<uint8_t>(row, col) = (uint8_t) scaledValue;
        }
    }

}