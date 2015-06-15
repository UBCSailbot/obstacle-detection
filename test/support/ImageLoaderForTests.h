//
// Created by paul on 10/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_IMAGELOADINGTEST_H
#define OBSTACLE_AVOIDANCE_IMAGELOADINGTEST_H

#include <gtest/gtest.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Resources.h"

class ImageLoaderForTests : public ::testing::Test {

protected:

    ImageLoaderForTests();

    cv::Mat _fishingBoatImg;
    cv::Mat _freighterSunImg;
    cv::Mat _garbledImg;

};


#endif //OBSTACLE_AVOIDANCE_IMAGELOADINGTEST_H
