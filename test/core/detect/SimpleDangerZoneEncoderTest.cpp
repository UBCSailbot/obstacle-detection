//
// Created by Aditi Chakravarthi on 15-08-09.
//

#include "SimpleDangerZoneEncoderTest.h"

TEST_F(SimpleDangerZoneEncoderTest, singleObstacle) {

    Horizon h(cv::Point2f(0, 30), cv::Point2f(80, 30));
    std::vector<Obstacle> obstacles;

    cv::Point2f p1(20, 40);
    cv::Point2f p2(40, 40);
    Obstacle o({p1, p2}, h);
    obstacles.push_back(o);

    ObstaclePositionFrame positions (frames, h, LeptonCameraSpecifications, obstacles);
    std::vector<DangerZone> zones = encoder.identifyDangerZones(positions);

    EXPECT_FLOAT_EQ(-12.75, zones[0].getPortAngleDeg());
    EXPECT_FLOAT_EQ(0.0, zones[0].getStarboardAngleDeg());
}

TEST_F(SimpleDangerZoneEncoderTest, passOnNoObstacles) {
    std::vector<Obstacle> emptyObstacles;
    ObstaclePositionFrame positions(frames, factory.makeNeutralHorizon(), LeptonCameraSpecifications,
        emptyObstacles);
    std::vector<DangerZone> zones = encoder.identifyDangerZones(positions);
    EXPECT_TRUE(zones.empty());
}

TEST_F(SimpleDangerZoneEncoderTest, multipleObstacles) {
    Horizon h(cv::Point2f(0, 40), cv::Point2f(80, 20));
    std::vector<Obstacle> obstacles;

    obstacles.push_back(Obstacle({cv::Point2f(7, 36), cv::Point2f(18,24), cv::Point2f(27,21)}, h));
    obstacles.push_back(Obstacle({cv::Point2f(78, 11), cv::Point2f(69,25)}, h));
    obstacles.push_back(Obstacle({cv::Point2f(37, 33), cv::Point2f(32,28), cv::Point2f(29,31)}, h));

    ObstaclePositionFrame positionFrame(frames, h, LeptonCameraSpecifications, obstacles);
    std::vector<DangerZone> zones = encoder.identifyDangerZones(positionFrame);

    EXPECT_EQ(obstacles.size(), zones.size());
    // TODO: Make this test more comprehensive
}

// TODO: Implement test
TEST_F(SimpleDangerZoneEncoderTest, rotatedClockwise) {

}

// TODO: Implement test
TEST_F(SimpleDangerZoneEncoderTest, rotatedCounterClockwise) {

}
