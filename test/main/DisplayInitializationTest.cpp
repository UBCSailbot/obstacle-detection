//
// Created by paul on 11/07/15.
//

#include "display/DisplayUtils.h"
#include <Resources.h>
#include <imageProc/rescale/Rescaler.h>
#include <imageProc/rescale/SimpleRescaler.h>

int main() {

    cv::Mat img = cv::imread(Resources::getImagePath("fishingBoat01.png"), CV_LOAD_IMAGE_UNCHANGED);

    Image16bit img16bit(img, false);
    Image8bit img8bit(img.rows, img.cols);

    Rescaler* r = new SimpleRescaler();
    r->scale16bitTo8bit(img16bit, img8bit);

    Display* display = DisplayUtils::connectToDisplay();

    cv::cvtColor(img, img, CV_GRAY2BGR);
    display->displayFrame(img8bit);
    cv::waitKey(0);

}