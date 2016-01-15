//
// Created by paul on 15/01/16.
//

#include "ObstacleTest.h"

#include <vector>
#include <opencv2/core/core.hpp>
#include <geometry/Horizon.h>
#include <detect/Obstacle.h>

TEST(ObstacleTest, getPortmostVertexEasy)
{
    cv::Point2f portmostVertex(0, 30);
    cv::Point2f p2(10, 50);

    std::vector<cv::Point2f> vertices;
    vertices.push_back(portmostVertex);
    vertices.push_back(p2);

    Horizon h(0, 0);

    Obstacle o(vertices);

    EXPECT_FLOAT_EQ(portmostVertex.x, o.getPortmostVertex(h).x);
    EXPECT_FLOAT_EQ(portmostVertex.y, o.getPortmostVertex(h).y);
}

TEST(ObstacleTest, getPortmostVertexRotated)
{
    cv::Point2f p2(60, 65);
    cv::Point2f portmostVertex(30, 70);

    std::vector<cv::Point2f> vertices;
    vertices.push_back(portmostVertex);
    vertices.push_back(p2);

    Horizon h(0.5, 0.1);

    Obstacle o(vertices);

    EXPECT_FLOAT_EQ(portmostVertex.x, o.getPortmostVertex(h).x);
    EXPECT_FLOAT_EQ(portmostVertex.y, o.getPortmostVertex(h).y);
}

TEST(ObstacleTest, getStarboardmostVertexEasy)
{
    cv::Point2f p1(0, 30);
    cv::Point2f starboardmostVertex(10, 50);

    std::vector<cv::Point2f> vertices;
    vertices.push_back(p1);
    vertices.push_back(starboardmostVertex);

    Horizon h(0, 0);

    Obstacle o(vertices);

    EXPECT_FLOAT_EQ(starboardmostVertex.x, o.getStarboardmostVertex(h).x);
    EXPECT_FLOAT_EQ(starboardmostVertex.y, o.getStarboardmostVertex(h).y);
}

TEST(ObstacleTest, getStarboardmostVertexRotated)
{
    cv::Point2f starboardmostVertex(25, 62);
    cv::Point2f p2(18, 58);

    std::vector<cv::Point2f> vertices;
    vertices.push_back(starboardmostVertex);
    vertices.push_back(p2);

    Horizon h(0.5, 0.1);

    Obstacle o(vertices);

    EXPECT_FLOAT_EQ(starboardmostVertex.x, o.getStarboardmostVertex(h).x);
    EXPECT_FLOAT_EQ(starboardmostVertex.y, o.getStarboardmostVertex(h).y);
}

TEST(ObstacleTest, negativeVerticalHorizon)
{
    // In this test, the horizon is nearly vertical. Down is to the right.
    cv::Point2f portmostVertex(61, 58);
    cv::Point2f starboardmostVertex(59, 62);

    std::vector<cv::Point2f> vertices;
    vertices.push_back(portmostVertex);
    vertices.push_back(starboardmostVertex);

    Horizon h(-1.55, 0.1);

    Obstacle o(vertices);

    EXPECT_FLOAT_EQ(starboardmostVertex.x, o.getStarboardmostVertex(h).x);
    EXPECT_FLOAT_EQ(starboardmostVertex.y, o.getStarboardmostVertex(h).y);
    EXPECT_FLOAT_EQ(portmostVertex.x, o.getPortmostVertex(h).x);
    EXPECT_FLOAT_EQ(portmostVertex.y, o.getPortmostVertex(h).y);
}

TEST(ObstacleTest, positiveVerticalHorizon)
{
    // In this test, the horizon is nearly vertical. Down is right.
    cv::Point2f portmostVertex(59, 62);
    cv::Point2f starboardmostVertex(61, 58);

    std::vector<cv::Point2f> vertices;
    vertices.push_back(portmostVertex);
    vertices.push_back(starboardmostVertex);

    Horizon h(1.55, 0.1);

    Obstacle o(vertices);

    EXPECT_FLOAT_EQ(starboardmostVertex.x, o.getStarboardmostVertex(h).x);
    EXPECT_FLOAT_EQ(starboardmostVertex.y, o.getStarboardmostVertex(h).y);
    EXPECT_FLOAT_EQ(portmostVertex.x, o.getPortmostVertex(h).x);
    EXPECT_FLOAT_EQ(portmostVertex.y, o.getPortmostVertex(h).y);
}

TEST(ObstacleTest, failOnTooFewVerts)
{
    cv::Point2f p(18, 58);

    std::vector<cv::Point2f> vertices;
    vertices.push_back(p);

    EXPECT_THROW(Obstacle o(vertices), std::invalid_argument);
}