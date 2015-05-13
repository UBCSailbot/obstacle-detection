//
// Created by paul on 12/05/15.
//

#include <opencv2/highgui/highgui.hpp>
#include "DesktopDisplay.h"

DesktopDisplay::DesktopDisplay() {

}


DesktopDisplay::~DesktopDisplay() {

}

void DesktopDisplay::displayFrame(cv::Mat image) {
    cv::imshow("Image", image);
}