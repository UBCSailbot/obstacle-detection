//
// Created by paul on 12/05/15.
//

#include <opencv2/highgui/highgui.hpp>
#include <types/Image8bit.h>
#include "DesktopDisplay.h"

DesktopDisplay::DesktopDisplay() {
    _connected = true;
}


DesktopDisplay::~DesktopDisplay() {

}

void DesktopDisplay::displayFrame(Image8bit image) {
    cv::imshow("Image", image);
    cv::waitKey(20);
}

void DesktopDisplay::displayColorFrame(cv::Mat image) {
    cv::imshow("Image Color", image);
    cv::waitKey(20);
}
