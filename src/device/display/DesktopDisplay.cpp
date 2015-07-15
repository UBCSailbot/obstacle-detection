//
// Created by paul on 12/05/15.
//

#include <opencv2/highgui/highgui.hpp>
#include <types/Image8bit.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "DesktopDisplay.h"

DesktopDisplay::DesktopDisplay() {
    _connected = true;
}


DesktopDisplay::~DesktopDisplay() {

}

void DesktopDisplay::display8bitGray(const Image8bit &image) {
    displayColored(image);
}

void DesktopDisplay::displayColored(const cv::Mat &image) {
    size_t xScaleFactor = 1;
    size_t yScaleFactor = 1;
    calculateScaleFactors(image, xScaleFactor, yScaleFactor);
    cv::Mat displayed;
    cv::resize(image, displayed, cv::Size(0,0), xScaleFactor, yScaleFactor, cv::INTER_NEAREST);
    cv::imshow("Image", displayed);
    cv::waitKey(20);
}

void DesktopDisplay::calculateScaleFactors(const cv::Mat &image, size_t &xScaleFactor, size_t &yScaleFactor) const {
    if (image.rows < MIN_HEIGHT) {
        yScaleFactor = MIN_HEIGHT / image.rows;
    }
    if (image.cols < MIN_WIDTH) {
        xScaleFactor = MIN_WIDTH / image.cols;
    }
    if (xScaleFactor > yScaleFactor) {
        yScaleFactor = xScaleFactor;
    }
    else if (yScaleFactor > xScaleFactor) {
        xScaleFactor = yScaleFactor;
    }
}
