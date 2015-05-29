//
// Created by paul on 11/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_HORIZONTEST_H
#define OBSTACLE_AVOIDANCE_HORIZONTEST_H

#include "gtest/gtest.h"
#include <opencv2/core/core.hpp>

#include "features/Horizon.h"

using namespace cv;

class HorizonTest : public ::testing::Test {

public:

    void testPointPosition(const Point2f &pointOfInterest, const Horizon &h, const bool &isAbove);
    void testGenerateHorizonFromEndpoints(const Point2f &start, const Point2f &end);

    Horizon generateHorizonFromEndpoints(const Point2f &start, const Point2f &end);

    double calculatePitchAngleFromEndpoints(const Point2f &start, const Point2f &end);
    double calculateRollAngleFromEndpoints(const Point2f &start, const Point2f &end);

};

#endif //OBSTACLE_AVOIDANCE_HORIZONTEST_H
