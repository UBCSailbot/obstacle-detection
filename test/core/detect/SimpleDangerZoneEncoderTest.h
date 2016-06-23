//
// Created by Aditi Chakravarthi on 15-08-09.
//

#ifndef OBSTACLE_AVOIDANCE_SIMPLEDANGERZONEENCODERTEST_H
#define OBSTACLE_AVOIDANCE_SIMPLEDANGERZONEENCODERTEST_H

#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>
#include <geometry/Horizon.h>
#include <geometry/HorizonFactory.h>
#include <memory>

#include "features/ObstaclePositionFrame.h"
#include "detect/DangerZone.h"
#include "detect/DangerZoneEncoder.h"
#include "detect/SimpleDangerZoneEncoder.h"

class SimpleDangerZoneEncoderTest : public testing::Test {

public:
    SimpleDangerZoneEncoderTest() {
        frames.push_back(std::shared_ptr<cv::Mat>(new Image8bit(LeptonCameraSpecifications.pixelHeight,
                                                       LeptonCameraSpecifications.pixelWidth)));
    }

    SimpleDangerZoneEncoder encoder = SimpleDangerZoneEncoder();
    HorizonFactory factory = HorizonFactory(LeptonCameraSpecifications);
    std::vector<std::shared_ptr<cv::Mat>> frames;


};


#endif //OBSTACLE_AVOIDANCE_SIMPLEDANGERZONEENCODERTEST_H
