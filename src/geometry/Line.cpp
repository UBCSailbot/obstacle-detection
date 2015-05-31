//
// Created by paul on 30/05/15.
//

#include "Line.h"

Line::Line(const cv::Point2f startPoint, const cv::Point2f endPoint) :
    _startPoint(startPoint), _endPoint(endPoint) {}

cv::Point2f Line::getStartPoint() const {
    return _startPoint;
}

cv::Point2f Line::getEndPoint() const {
    return _endPoint;
}
