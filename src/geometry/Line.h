//
// Created by paul on 30/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_LINE_H
#define OBSTACLE_AVOIDANCE_LINE_H


#include <opencv2/core/core.hpp>

/**
 * A simple, immutable class that represents a two-dimensional line, defined
 *  by a starting point and an endpoint.
 */
class Line {

public:
    Line(const cv::Point2f startPoint, const cv::Point2f endPoint);
    const cv::Point2f start;
    const cv::Point2f end;
};


#endif //OBSTACLE_AVOIDANCE_LINE_H
