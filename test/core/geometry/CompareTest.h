//
// Created by paul on 05/02/16.
//

#ifndef OBSTACLE_DETECTION_COMPARETEST_H
#define OBSTACLE_DETECTION_COMPARETEST_H

#include <gtest/gtest.h>

#include <geometry/Compare.h>


class CompareTest : public ::testing::Test {

public:
    static double constexpr testAnglePrecision = M_PI / 1800;

    static double constexpr testCoordinatePrecision = 0.00000001;

    static double constexpr testMagnitudePrecision = testCoordinatePrecision * 100;
};


#endif //OBSTACLE_DETECTION_COMPARETEST_H
