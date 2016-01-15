//
// Created by paul on 15/01/16.
//

#ifndef OBSTACLE_DETECTION_OBSTACLE_H
#define OBSTACLE_DETECTION_OBSTACLE_H

#include <vector>
#include <limits>
#include <opencv2/core/core.hpp>
#include <geometry/Horizon.h>

/**
 * Describes an obstacle as a set of points on the coordinate plane of an image.
 */
class Obstacle {

public:
    Obstacle(const std::vector<cv::Point2f> vertices);

    const std::vector<cv::Point2f> getVertices() const;

    const cv::Point2f getPortmostVertex(Horizon frameOfReference);

    const cv::Point2f getStarboardmostVertex(Horizon frameOfReference);

    size_t numVertices() const;

private:
    std::vector<cv::Point2f> _vertices;
    cv::Point2f _portmostVertex;
    bool _portmostSet;
    cv::Point2f _starboardmostVertex;
    bool _starboardmostSet;
};

#endif //OBSTACLE_DETECTION_OBSTACLE_H
