//
// Created by paul on 12/05/15.
//

#include "DesktopDisplay.h"

DesktopDisplay::DesktopDisplay() : DesktopDisplay("Display") { }

DesktopDisplay::DesktopDisplay(std::string windowName) : _windowName(windowName) {
    _connected = true;
}

const size_t DesktopDisplay::MIN_WIDTH = 640;
const size_t DesktopDisplay::MIN_HEIGHT = 480;

DesktopDisplay::~DesktopDisplay() {

}

void DesktopDisplay::display8bitGray(const Image8bit &image) {
    displayColored(image);
}

void DesktopDisplay::displayColored(const cv::Mat &image) {
    size_t scaleFactor = DisplayUtils::calculateScaleFactor(image, MIN_WIDTH, MIN_HEIGHT);
    cv::Mat displayed;
    cv::resize(image, displayed, cv::Size(0, 0), scaleFactor, scaleFactor, cv::INTER_NEAREST);
    cv::imshow(_windowName, displayed);
    cv::waitKey(20);
}
