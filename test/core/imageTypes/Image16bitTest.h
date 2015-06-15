//
// Created by paul on 12/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_IMAGE16BITTEST_H
#define OBSTACLE_AVOIDANCE_IMAGE16BITTEST_H

#include <gtest/gtest.h>

#include <vector>

#include <opencv2/core/core.hpp>

#include "imageTypes/Image16bit.h"

class Image16bitTest : public ::testing::Test {
protected:
    Image16bitTest();

    cv::Mat _m1;
    int _size1 = 4;
};


#endif //OBSTACLE_AVOIDANCE_IMAGE16BITTEST_H
