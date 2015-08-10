//
// Created by Aditi Chakravarthi on 15-08-09.
//
#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>
#include <geometry/Horizon.h>

#include "detect/ObstaclePositionFrame.h"
#include "detect/DangerZone.h"
#include "detect/DangerZoneEncoder.h"
#include "detect/SimpleDangerZoneEncoder.h"


TEST(SimpleDangerZoneEncoderTest, doesItWork) {

    SimpleDangerZoneEncoder encoder;
    std::vector<std::pair<double, double>> obstacleEdges;
    obstacleEdges.push_back(std::make_pair(20.0,40.0));
    Horizon h (0,0);
    cv::Mat frame = cv::Mat(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX, CV_16UC1, cv::Scalar(0));
    ObstaclePositionFrame positions (frame, 51, 37,obstacleEdges);
    encoder.identifyDangerZones(positions,h);
    std::vector<DangerZone> zones = encoder.identifyDangerZones(positions,h);


    EXPECT_FLOAT_EQ(zones[0].getPortAngleDeg(), -12.75);
    EXPECT_FLOAT_EQ(zones[0].getStarboardAngleDeg(), 0.0);
}