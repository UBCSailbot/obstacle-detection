//
// Created by paul on 19/07/15.
//

#include "display/DisplayUtils.h"

Display *DisplayUtils::connectToDisplay() {
    Display *display = new RoboPeakUSBDisplay();
    if (!display->connected()) {
        delete display;
        display = new DesktopDisplay();
    }
    return display;
}

void DisplayUtils::displayFrameWithHorizonLine(const Image8bit &frame, const Horizon &h, Display &d) {
    cv::Mat displayed(frame.rows, frame.cols, CV_16U);
    cv::cvtColor(frame, displayed, cv::COLOR_GRAY2BGR);
    cv::line(displayed, h.getStartPoint(), h.getEndPoint(), cv::Scalar(255, 0, 0), 1);
    d.displayColored(displayed);
}

void DisplayUtils::rescaleAndDisplay(Image16bit img, Rescaler *r, Display &d) {
    Image8bit img8bit(img.rows, img.cols);

    r->scale16bitTo8bit(img, img8bit);

    d.display8bitGray(img8bit);

}

/**
 * Returns the constant factor by which an image should be scaled to fill up at least one
 *  of the dimensions of a display, while preserving the aspect ratio of the original image.
 */
size_t DisplayUtils::calculateScaleFactor(const cv::Mat &image, const size_t &displayWidth,
                                          const size_t &displayHeight) {
    size_t xScaleFactor = 1;
    size_t yScaleFactor = 1;

    if (image.rows < displayHeight) {
        yScaleFactor = displayHeight / image.rows;
    }
    if (image.cols < displayWidth) {
        xScaleFactor = displayWidth / image.cols;
    }

    if (xScaleFactor > yScaleFactor) {
        return (int) yScaleFactor;
    }
    else {
        return (int) xScaleFactor;
    }
}