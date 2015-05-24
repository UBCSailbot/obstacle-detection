//
// Created by paul on 11/05/15.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include "HorizonTest.h"

using namespace std;

// TODO: Fix these tests.
void testIsAboveHorizon() {

    cv::Point2f start, end, pointOfInterest;

    start = cv::Point2f(0,0);
    end = cv::Point2f(80,80);
    pointOfInterest = cv::Point2f(30,31);

    double rollRad = atan2(60, 80);

    Horizon h(rollRad, 0);

    if (h.isPointAbove(pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;

    pointOfInterest = cv::Point2f(30,29);

    if (!h.isPointAbove(pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;


    pointOfInterest = cv::Point2f(40,40);

    if (h.isPointAbove(pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;


    start = cv::Point2f(0,20);
    end = cv::Point2f(80,40);
    pointOfInterest = cv::Point2f(40,41);

    if (h.isPointAbove(pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;


    start = cv::Point2f(0,20);
    end = cv::Point2f(80,40);
    pointOfInterest = cv::Point2f(40,19);

    if (!h.isPointAbove(pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;


    start = cv::Point2f(20,0);
    end = cv::Point2f(0,20);
    pointOfInterest = cv::Point2f(30,31);

    if (h.isPointAbove(pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;


    start = cv::Point2f(60,80);
    end = cv::Point2f(80,60);
    pointOfInterest = cv::Point2f(30,31);

    if (!h.isPointAbove(pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;


    start = cv::Point2f(20,80);
    end = cv::Point2f(60,0);
    pointOfInterest = cv::Point2f(50,40);

    if (h.isPointAbove(pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;

}

void testHorizon() {
    testIsAboveHorizon();
}
