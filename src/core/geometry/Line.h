//
// Created by paul on 30/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_LINE_H
#define OBSTACLE_AVOIDANCE_LINE_H


#include <opencv2/core/core.hpp>

/**
 * A simple class that represents a two-dimensional line, as defined
 *  by two points. Although this class defines one of these points
 *  to be a "start point" and the other to be an "end point", in fact
 *  the geometric entity represented by this class should be considered
 *  to be directionless.
 */
class Line {

public:
    Line(const cv::Point2f startPoint, const cv::Point2f endPoint);
    cv::Point2f getStartPoint() const;
    cv::Point2f getEndPoint() const;

    bool operator==(const Line &other) const;

protected:
    cv::Point2f _startPoint;
    cv::Point2f _endPoint;

};


#endif //OBSTACLE_AVOIDANCE_LINE_H
