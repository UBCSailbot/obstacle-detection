//
// Created by paul on 26/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_IMAGEHISTOGRAMTEST_H
#define OBSTACLE_AVOIDANCE_IMAGEHISTOGRAMTEST_H

#include <iostream>
#include <gtest/gtest.h>
#include <geometry/Horizon.h>

#include <opencv2/core/core.hpp>
#include <imageProc/core/HorizonImageHistogram.h>

class HorizonImageHistogramTest : public ::testing::Test {

public:
    HorizonImageHistogramTest();

protected:
    static const int imageRows = 60;
    static const int imageCols = 80;

    Horizon horizonBelowFrame;

    static cv::Mat makeThreeEvenPixelValues(const int &pixelValue0,
                                            const int &pixelValue1,
                                            const int &pixelValue2);
};


#endif //OBSTACLE_AVOIDANCE_IMAGEHISTOGRAMTEST_H
