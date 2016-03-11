//
// Created by paul on 30/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_LINE_H
#define OBSTACLE_AVOIDANCE_LINE_H


#include <opencv2/core/core.hpp>
#include "Vector2d.h"

/**
 * A simple class that represents a two-dimensional line, as defined
 *  by a vector and a point.
 */
class Line {

  public:
    Line(const cv::Point2f startPoint, const cv::Point2f endPoint);

    Vector2d getVector() const;
    cv::Point2f getStartPoint() const;
    cv::Point2f getEndPoint() const;

    /**
     * Determines equality between two lines, based on whether their
     *  point-vector representation is equivalent. That is: returns
     *  [whether they have the same y-intercept] && [whether their
     *  vectors are pointing in the same direction].
     */
    bool operator==(const Line &other) const;

    double calculateMagnitude() const;

    /**
     * Projects the point onto this line and returns the distance of the
     *  projected point from the left endpoint of this line.
     */
    double findPointClosestTo(const cv::Point2f pointOfInterest) const;

    /**
     * Returns whether this line is parallel to the given line.
     */
    bool isParallelTo(const Line &other) const;

    /**
     * Returns whether this line is parallel to the given vector.
     */
    bool isParallelTo(const Vector2d &other) const;

    static Line fromEndpoints(cv::Point2f p1, cv::Point2f p2);

  protected:
    cv::Point2f _startPoint;
    cv::Point2f _endPoint;

    /**
     * Used for storing the point-vector representation of this line.
     */
    cv::Point2f _y_intercept;

    /**
     * A vector that, when starting from a point on this line, points
     *  in the direction of this line.
     */
    Vector2d _vector;

    // For performing certain geometric operations it is useful to store a
    //  representation of this line as a vector starting from the origin.
    float _xComponent, _yComponent;

};


#endif //OBSTACLE_AVOIDANCE_LINE_H
