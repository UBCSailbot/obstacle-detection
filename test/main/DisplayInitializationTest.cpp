//
// Created by paul on 11/07/15.
//

#include "display/DisplayUtils.h"
#include <Resources.h>

int main() {

    cv::Mat img = cv::imread(Resources::getImagePath("16bit/fishingBoat01.png"), CV_LOAD_IMAGE_UNCHANGED);
    Image16bit img16bit(img, false);

    Display* display = DisplayUtils::connectToDisplay();

    Rescaler* r = new SimpleRescaler();
    DisplayUtils::rescaleAndDisplay(img16bit, r, *display);
    cv::waitKey(0);

}