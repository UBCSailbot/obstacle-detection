//
// Created by Derek Lun on 5/23/2015.
//

#include "SunImageTest.h"

void SunImageTest::testFindSun() {

    cv::Point2i start, end, pointOfInterest;

    start = cv::Point2f(0,0);
    end = cv::Point2f(80,80);
    pointOfInterest = cv::Point2f(30,31);

    const unsigned int minSunPixelValue = 9001;
    const int margin = 2;
    double rollRad = atan2(60, 80);

    Horizon h(rollRad, 0);

    //SunImage si(h, frame, minSunPixelValue, margin);
}

void SunImageTest::runTests() {
    testFindSun();
}