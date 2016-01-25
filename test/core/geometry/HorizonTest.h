//
// Created by paul on 11/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_HORIZONTEST_H
#define OBSTACLE_AVOIDANCE_HORIZONTEST_H

#include "gtest/gtest.h"
#include <opencv2/core/core.hpp>
#include <geometry/Horizon.h>
#include <geometry/HorizonFactory.h>
#include "camera/lepton/LeptonCameraSpecifications.h"


class HorizonTest : public ::testing::Test {

public:

    void testIsPointAbove(const cv::Point2f &pointOfInterest, const Horizon &h, const bool &isAbove);

    HorizonFactory hf = HorizonFactory(LeptonCameraSpecifications);

};

#endif //OBSTACLE_AVOIDANCE_HORIZONTEST_H
