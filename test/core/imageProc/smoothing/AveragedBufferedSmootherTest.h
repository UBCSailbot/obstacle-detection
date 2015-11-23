//
// Created by paul on 07/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_VALUESMOOTHENERTEST_H
#define OBSTACLE_AVOIDANCE_VALUESMOOTHENERTEST_H

#include <gtest/gtest.h>
#include "imageProc/smoothing/WeightedAverageBufferedSmoother.h"

class AveragedBufferedSmootherTest : public ::testing::Test {

protected:
    static void testSimpleSmoothing(int bufferSize, int outlier);
};


#endif //OBSTACLE_AVOIDANCE_VALUESMOOTHENERTEST_H
