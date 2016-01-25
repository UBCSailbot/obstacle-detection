//
// Created by paul on 15/01/16.
//

#include "ObstacleTest.h"

#include <vector>
#include <opencv2/core/core.hpp>
#include <geometry/Horizon.h>
#include <detect/Obstacle.h>
#include <geometry/Orientation.h>
#include <geometry/HorizonFactory.h>
#include <camera/lepton/LeptonCameraSpecifications.h>

TEST_F(ObstacleTest, getPortmostVertexEasy)
{
    cv::Point2f portmostVertex(0, 30);
    cv::Point2f p2(10, 50);

    std::vector<cv::Point2f> vertices;
    vertices.push_back(portmostVertex);
    vertices.push_back(p2);

    Horizon h = _factory.makeHorizon(Orientation{0, 0, 0});

    Obstacle o(vertices, h);

    EXPECT_FLOAT_EQ(portmostVertex.x, o.getPortmostVertex().x);
    EXPECT_FLOAT_EQ(portmostVertex.y, o.getPortmostVertex().y);
}

TEST_F(ObstacleTest, getPortmostVertexRotated)
{
    cv::Point2f p2(60, 65);
    cv::Point2f portmostVertex(30, 70);

    std::vector<cv::Point2f> vertices;
    vertices.push_back(portmostVertex);
    vertices.push_back(p2);

    Horizon h = _factory.makeHorizon(Orientation{0.5, 0.1, 0});

    Obstacle o(vertices, h);

    EXPECT_FLOAT_EQ(portmostVertex.x, o.getPortmostVertex().x);
    EXPECT_FLOAT_EQ(portmostVertex.y, o.getPortmostVertex().y);
}

TEST_F(ObstacleTest, getStarboardmostVertexEasy)
{
    cv::Point2f p1(0, 30);
    cv::Point2f starboardmostVertex(10, 50);

    std::vector<cv::Point2f> vertices;
    vertices.push_back(p1);
    vertices.push_back(starboardmostVertex);

    Horizon h = _factory.makeHorizon(Orientation{0, 0, 0});

    Obstacle o(vertices, h);

    EXPECT_FLOAT_EQ(starboardmostVertex.x, o.getStarboardmostVertex().x);
    EXPECT_FLOAT_EQ(starboardmostVertex.y, o.getStarboardmostVertex().y);
}

TEST_F(ObstacleTest, getStarboardmostVertexRotated)
{
    cv::Point2f starboardmostVertex(25, 62);
    cv::Point2f p2(18, 58);

    std::vector<cv::Point2f> vertices;
    vertices.push_back(starboardmostVertex);
    vertices.push_back(p2);

    Horizon h = _factory.makeHorizon(Orientation{0.5, 0.1, 0.0});

    Obstacle o(vertices, h);

    EXPECT_FLOAT_EQ(starboardmostVertex.x, o.getStarboardmostVertex().x);
    EXPECT_FLOAT_EQ(starboardmostVertex.y, o.getStarboardmostVertex().y);
}

TEST_F(ObstacleTest, negativeVerticalHorizon)
{
    // In this test, the horizon is nearly vertical. Down is to the right.
    cv::Point2f starboardmostVertex(61, 58);
    cv::Point2f portmostVertex(59, 62);

    std::vector<cv::Point2f> vertices;
    vertices.push_back(portmostVertex);
    vertices.push_back(starboardmostVertex);

    Horizon h = _factory.makeHorizon(Orientation{-1.55, 0.1, 0});

    Obstacle o(vertices, h);

    EXPECT_FLOAT_EQ(starboardmostVertex.x, o.getStarboardmostVertex().x);
    EXPECT_FLOAT_EQ(starboardmostVertex.y, o.getStarboardmostVertex().y);
    EXPECT_FLOAT_EQ(portmostVertex.x, o.getPortmostVertex().x);
    EXPECT_FLOAT_EQ(portmostVertex.y, o.getPortmostVertex().y);
}

TEST_F(ObstacleTest, positiveVerticalHorizon)
{
    // In this test, the horizon is nearly vertical. Down is right.
    cv::Point2f starboardmostVertex(59, 62);
    cv::Point2f portmostVertex(61, 58);

    std::vector<cv::Point2f> vertices;
    vertices.push_back(portmostVertex);
    vertices.push_back(starboardmostVertex);

    Horizon h = _factory.makeHorizon(Orientation{1.55, 0.1, 0});

    Obstacle o(vertices, h);

    EXPECT_FLOAT_EQ(starboardmostVertex.x, o.getStarboardmostVertex().x);
    EXPECT_FLOAT_EQ(starboardmostVertex.y, o.getStarboardmostVertex().y);
    EXPECT_FLOAT_EQ(portmostVertex.x, o.getPortmostVertex().x);
    EXPECT_FLOAT_EQ(portmostVertex.y, o.getPortmostVertex().y);
}

TEST_F(ObstacleTest, failOnTooFewVerts)
{
    cv::Point2f p(18, 58);

    std::vector<cv::Point2f> vertices;
    vertices.push_back(p);

    EXPECT_THROW(Obstacle o(vertices, _factory.makeNeutralHorizon()), std::invalid_argument);
}