#include "opencv2/core/types_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;


bool isAboveHorizon(cv::Point2f start, cv::Point2f end, cv::Point2f pointOfInterest)
{
    if (pointOfInterest.y > start.y && pointOfInterest.y > end.y)
        return true;

    if (pointOfInterest.y < start.y && pointOfInterest.y < end.y)
        return false;

    if (pointOfInterest.x > start.x && pointOfInterest.x > end.x)
        return false;

    if (pointOfInterest.x < start.x && pointOfInterest.x < end.x)
        return true;

    if ((end.x - start.x) * pointOfInterest.x < (end.y - start.y) * pointOfInterest.y)
        return true;
}

/** @function main */
int main( int argc, char** argv )
{
    cv::Point2f start, end, pointOfInterest;

    start = cv::Point2f(0,0);
    end = cv::Point2f(80,80);
    pointOfInterest = cv::Point2f(30,31);

    if (isAboveHorizon(start, end, pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;

    start = cv::Point2f(0,0);
    end = cv::Point2f(80,80);
    pointOfInterest = cv::Point2f(30,29);

    if (!isAboveHorizon(start, end, pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;


    start = cv::Point2f(0,0);
    end = cv::Point2f(80,80);
    pointOfInterest = cv::Point2f(40,40);

    if (isAboveHorizon(start, end, pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;


    start = cv::Point2f(0,20);
    end = cv::Point2f(80,40);
    pointOfInterest = cv::Point2f(40,41);

    if (isAboveHorizon(start, end, pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;


    start = cv::Point2f(0,20);
    end = cv::Point2f(80,40);
    pointOfInterest = cv::Point2f(40,19);

    if (!isAboveHorizon(start, end, pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;


    start = cv::Point2f(20,0);
    end = cv::Point2f(0,20);
    pointOfInterest = cv::Point2f(30,31);

    if (isAboveHorizon(start, end, pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;


    start = cv::Point2f(60,80);
    end = cv::Point2f(80,60);
    pointOfInterest = cv::Point2f(30,31);

    if (!isAboveHorizon(start, end, pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;


    start = cv::Point2f(20,80);
    end = cv::Point2f(60,0);
    pointOfInterest = cv::Point2f(50,40);

    if (isAboveHorizon(start, end, pointOfInterest))
        std::cout << "pass" << endl;
    else
        std::cout << "failed" << endl;

}
