#include "SunImage.h"
#include <iostream>

SunImage::SunImage(const Horizon &horizon, const cv::Mat &frame, unsigned int minSunPixelValue, int margin) : horizon(horizon), frame(frame), minSunPixelValue(minSunPixelValue), margin(margin) {
}

SunImage::~SunImage() {
}

void SunImage::findSun() {
    for (int row = 0; row < frame.rows; row++) {
        for (int col = 0; col < frame.cols; col++) {
            unsigned int value = frame.at<uint16_t>(row, col);

            if (value >= minSunPixelValue) {
            	if (row > sunBottom)
            		sunBottom = row;
            	else if (row < sunTop)
            		sunTop = row;
            	if (col < sunLeft)
            		sunLeft = col;
            	else if (col > sunRight)
            		sunRight = col;
            }
        }
    }

    std::cout << "sunBottom is" << sunBottom << std::endl;
    std::cout << "sunTop is" << sunTop << std::endl;
    std::cout << "sunLeft is" << sunLeft << std::endl;
    std::cout << "sunRight is" << sunRight << std::endl;

}

// uint sunRadius() {
// }