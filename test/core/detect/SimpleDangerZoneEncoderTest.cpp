//
// Created by Aditi Chakravarthi on 15-08-09.
//

#include "SimpleDangerZoneEncoderTest.h"

TEST(SimpleDangerZoneEncoderTest, doesItWork) {

    SimpleDangerZoneEncoder encoder(LeptonCameraSpecifications);
    std::vector<Obstacle> obstacles;
    cv::Point2f p1(20, 40);
    cv::Point2f p2(40, 40);
    Horizon h(cv::Point2f(0, 30), cv::Point2f(80, 30));
    Obstacle o({p1, p2}, h);
    obstacles.push_back(o);
    cv::Mat frame = cv::Mat(LeptonCameraSpecifications.pixelHeight,
                            LeptonCameraSpecifications.pixelWidth,
                            CV_16UC1, cv::Scalar(0));
    ObstaclePositionFrame positions (frame, h, LeptonCameraSpecifications, obstacles);
    std::vector<DangerZone> zones = encoder.identifyDangerZones(positions);

    EXPECT_FLOAT_EQ(-12.75, zones[0].getPortAngleDeg());
    EXPECT_FLOAT_EQ(0.0, zones[0].getStarboardAngleDeg());
}