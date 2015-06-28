//
// Created by paul on 12/05/15.
//

#include <opencv2/highgui/highgui.hpp>
#include <types/Image8bit.h>
#include "DesktopDisplay.h"

DesktopDisplay::DesktopDisplay() {

}


DesktopDisplay::~DesktopDisplay() {

}

void DesktopDisplay::displayFrame(Image8bit image) {
    cv::imshow("Image", image);
    cv::waitKey(20);
}
