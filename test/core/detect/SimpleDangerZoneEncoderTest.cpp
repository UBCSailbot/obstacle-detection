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
    std::vector<Obstacle> obstacles;
    cv::Point2f p1(20, 40);
    cv::Point2f p2(40, 40);
    Obstacle o({p1, p2});
    obstacles.push_back(o);
    Horizon h (0,0);
    cv::Mat frame = cv::Mat(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX, CV_16UC1, cv::Scalar(0));
    ObstaclePositionFrame positions (frame, 51, 37, obstacles);
    std::vector<DangerZone> zones = encoder.identifyDangerZones(positions,h);


    EXPECT_FLOAT_EQ(zones[0].getPortAngleDeg(), -12.75);
    EXPECT_FLOAT_EQ(zones[0].getStarboardAngleDeg(), 0.0);
}