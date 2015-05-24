//
// Created by paul on 11/05/15.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <iomanip>
#include "HorizonTest.h"


void HorizonTest::testIsAboveHorizon() {

    testStable();

    testOnlyPositiveRoll();
    testOnlyNegativeRoll();

    testOnlyPositivePitch();
    testOnlyNegativePitch();

    testPositiveRollNegativePitch();
    testNegativeRollPositivePitch();

}

void HorizonTest::testStable() const {
    Point2f pointOfInterest;
    Horizon h(0,0);

    pointOfInterest = Point2f(69,20);
    testPointPosition(pointOfInterest, h, true, "only positive roll, above");

    pointOfInterest = Point2f(30,31);
    testPointPosition(pointOfInterest, h, false, "only positive roll, below");

    pointOfInterest = Point2f(79,30);
    testPointPosition(pointOfInterest, h, false, "only positive roll, onto");
}

void HorizonTest::testOnlyPositiveRoll() const {
    Point2f pointOfInterest;
    Horizon h = generateHorizonFromEndpoints(Point2f(0, 0), Point2f(80,60));

    pointOfInterest = Point2f(30,20);
    testPointPosition(pointOfInterest, h, true, "only positive roll, above");

    pointOfInterest = Point2f(30,29);
    testPointPosition(pointOfInterest, h, false, "only positive roll, below");

    pointOfInterest = Point2f(30,22.5);
    testPointPosition(pointOfInterest, h, false, "only positive roll, onto");
}

void HorizonTest::testOnlyNegativeRoll() const {
    Point2f pointOfInterest;
    Horizon h = generateHorizonFromEndpoints(Point2f(0, 60), Point2f(80,0));

    pointOfInterest = Point2f(60,10);
    testPointPosition(pointOfInterest, h, true, "only negative roll, above");

    pointOfInterest = Point2f(60,29);
    testPointPosition(pointOfInterest, h, false, "only negative roll, below");

    pointOfInterest = Point2f(60,15);
    testPointPosition(pointOfInterest, h, false, "only negative roll, onto");
}

void HorizonTest::testOnlyPositivePitch() const {
    Point2f pointOfInterest;
    Horizon h = generateHorizonFromEndpoints(Point2f(0, 40), Point2f(80, 40));

    pointOfInterest = cv::Point2f(25,20);
    testPointPosition(pointOfInterest, h, true, "only positive pitch, above");

    pointOfInterest = cv::Point2f(25,50);
    testPointPosition(pointOfInterest, h, false, "only positive pitch, below");

    pointOfInterest = cv::Point2f(25,40);
    testPointPosition(pointOfInterest, h, false, "only positive pitch, onto");
}

void HorizonTest::testOnlyNegativePitch() const {
    Point2f pointOfInterest;
    Horizon h = generateHorizonFromEndpoints(Point2f(0, 20), Point2f(80, 20));

    pointOfInterest = cv::Point2f(18,18);
    testPointPosition(pointOfInterest, h, true, "only negative pitch, above");

    pointOfInterest = cv::Point2f(47,29);
    testPointPosition(pointOfInterest, h, false, "only negative pitch, below");

    pointOfInterest = cv::Point2f(18,20);
    testPointPosition(pointOfInterest, h, false, "only negative pitch, onto");
}

void HorizonTest::testPositiveRollNegativePitch() const {

}

void HorizonTest::testNegativeRollPositivePitch() const {

}



double HorizonTest::calculatePitchAngleFromEndpoints(const Point2f &start, const Point2f &end) const {
    double middleHeight = (start.y + end.y) / 2;
    double delta = middleHeight - (double) VIEWPORT_HEIGHT_PIX/2;
    double fovVerticalRad = (double) VIEWPORT_FOV_DEGREES_VERTICAL / 180 * M_PI;
    return delta * fovVerticalRad / VIEWPORT_HEIGHT_PIX ;
}

Horizon HorizonTest::generateHorizonFromEndpoints(const Point2f &start, const Point2f &end) const {

    double pitchRad = calculatePitchAngleFromEndpoints(start, end);
    double rollRad = calculateRollAngleFromEndpoints(start, end);
    Horizon h(rollRad, pitchRad);
    return h;
}

double HorizonTest::calculateRollAngleFromEndpoints(const Point2f &start, const Point2f &end) const {
    double rollRad = atan2(end.y - start.y, end.x - start.x);
    return rollRad;
}

void HorizonTest::testPointPosition(const Point2f &pointOfInterest, const Horizon &h,
                                      const bool &isAbove, const string &testTitle) const {
    if (isAbove == h.isPointAbove(pointOfInterest))
        cout << setiosflags(ios::left) << "HorizonTest, " << setw(30) << testTitle << ": pass" << endl;
    else
        cout << setiosflags(ios::left) << "HorizonTest, " << setw(30) << testTitle << ": failed" << endl;
}

void HorizonTest::testHorizon() {
    testIsAboveHorizon();
}

