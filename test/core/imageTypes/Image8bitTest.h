//
// Created by paul on 14/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_IMAGE8BITTEST_H
#define OBSTACLE_AVOIDANCE_IMAGE8BITTEST_H

#include <gtest/gtest.h>

#include <vector>

#include <opencv2/core/core.hpp>

#include "types/Image8bit.h"

class Image8bitTest : public ::testing::Test {
protected:
    Image8bitTest();

    cv::Mat _m1;
    int _size1 = 4;
};

#endif //OBSTACLE_AVOIDANCE_IMAGE8BITTEST_H
