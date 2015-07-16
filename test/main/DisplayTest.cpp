//
// Created by paul on 15/07/15.
//

#include <iostream>

#include <Resources.h>
#include <types/Image16bit.h>
#include <imageProc/rescale/Rescaler.h>
#include <imageProc/rescale/SimpleRescaler.h>
#include <display/DisplayUtils.h>
#include "display/RoboPeakUSBDisplay.h"

using namespace cv;
using namespace std;

void testDisplay8bitGray(Display* d, Image8bit img) {
    d->display8bitGray(img);
    waitKey(0);
}

void testDisplayColored(Display* d, cv::Mat img) {
    line(img, Point(10,10), Point(80,60), Scalar(255,255,0), 1);
    d->displayColored(img);
    waitKey(0);
}

int main() {

    Display* d = DisplayUtils::connectToDisplay();

    Mat img = imread(Resources::getImagePath("fishingBoat01.png"), CV_LOAD_IMAGE_UNCHANGED);
    Image16bit img16bit(img, false);

    Image8bit img8bit(img.rows, img.cols);
    Rescaler* r = new SimpleRescaler();
    r->scale16bitTo8bit(img16bit, img8bit);

    testDisplay8bitGray(d, img8bit);

    Mat color(img.rows, img.cols, CV_8UC3);
    cvtColor(img8bit, color, COLOR_GRAY2BGR);

    testDisplayColored(d, color);

    cout << "Display tests passed successfully :)" << endl;

}
