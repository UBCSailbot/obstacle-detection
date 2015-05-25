//
// Created by Derek Lun on 5/23/2015.
//

#include "SunImageTest.h"

void SunImageTest::testSunImage() {
    testFindSun();
}

void SunImageTest::testFindSun() const {
    cv::Point2i start, end, pointOfInterest;

    start = cv::Point2f(0,0);
    end = cv::Point2f(80,80);
    pointOfInterest = cv::Point2f(30,31);
    cv::Mat frame = cv::imread( "/img/sunImgTest01.png");
    unsigned int minSunPixelValue = 9001;
    int margin = 2;

    Horizon h(0, 0);

    //SunImage si(h, frame, minSunPixelValue, margin);
}

