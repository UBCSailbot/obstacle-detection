//
// Created by paul on 30/05/15.
//

#include "LineTest.h"

#include "opencv2/core/core.hpp"

#include <gtest/gtest.h>

#include "geometry/Line.h"

TEST(LineTest, immutability) {
    Line line1(cv::Point2f(0,0), cv::Point2f(80, 60));

    // If this line is uncommented, it should generate a compilation error.
    // This is kind of a crappy test, but was useful during development.
//    line1.end = cv::Point2f(10,10);

}