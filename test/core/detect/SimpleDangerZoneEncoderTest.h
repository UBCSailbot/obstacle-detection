//
// Created by Aditi Chakravarthi on 15-08-09.
//

#ifndef OBSTACLE_AVOIDANCE_SIMPLEDANGERZONEENCODERTEST_H
#define OBSTACLE_AVOIDANCE_SIMPLEDANGERZONEENCODERTEST_H

#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>
#include <geometry/Horizon.h>
#include <geometry/HorizonFactory.h>

#include "features/ObstaclePositionFrame.h"
#include "detect/DangerZone.h"
#include "detect/DangerZoneEncoder.h"
#include "detect/SimpleDangerZoneEncoder.h"

class SimpleDangerZoneEncoderTest : public testing::Test {

public:
    SimpleDangerZoneEncoder encoder = SimpleDangerZoneEncoder(LeptonCameraSpecifications);
    Image8bit frame = Image8bit(LeptonCameraSpecifications.pixelHeight,
                                LeptonCameraSpecifications.pixelWidth);
    HorizonFactory factory = HorizonFactory(LeptonCameraSpecifications);


};


#endif //OBSTACLE_AVOIDANCE_SIMPLEDANGERZONEENCODERTEST_H
