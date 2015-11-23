//
// Created by paul on 25/05/15.
//

#include "Rescaling.h"

void Rescaling::clipTo8bitsCompress2to1(const Image16bit &src, Image8bit &dst, const int &newMidPixelValue) {
    assert(dst.size == src.size);

    for (int row = 0; row < src.rows; row++) {
        for (int col = 0; col < src.cols; col++) {
            int scaledValue = src.at<uint16_t>(row, col) - newMidPixelValue + 255;
            if (scaledValue > 511)
                scaledValue = 511;
            else if (scaledValue < 0)
                scaledValue = 0;
            dst.at<uint8_t>(row, col) = (uint8_t) (scaledValue / 2);
        }
    }

}

void Rescaling::clipTo8bitsNoCompression(const Image16bit &src, Image8bit &dst, const int &newMidPixelValue) {
    assert(dst.size == src.size);

    for (int row = 0; row < src.rows; row++) {
        for (int col = 0; col < src.cols; col++) {
            int scaledValue = src.at<uint16_t>(row, col) - newMidPixelValue + 127;
            if (scaledValue > 255)
                scaledValue = 255;
            else if (scaledValue < 0)
                scaledValue = 0;
            dst.at<uint8_t>(row, col) = (uint8_t) scaledValue;
        }
    }

}