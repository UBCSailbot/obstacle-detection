//
// Created by paul on 30/05/15.
//

#include "Line.h"

Line::Line(const cv::Point2f startPoint, const cv::Point2f endPoint) :
    _startPoint(startPoint), _endPoint(endPoint),
    _vector(_endPoint.x - _startPoint.x, _endPoint.y - _startPoint.y) {
    _xComponent = _endPoint.x - _startPoint.x;
    _yComponent = _endPoint.y - _startPoint.y;
}

Vector2d Line::getVector() const {
    return _vector;
}

cv::Point2f Line::getStartPoint() const {
    return _startPoint;
}

cv::Point2f Line::getEndPoint() const {
    return _endPoint;
}

bool Line::operator==(const Line &other) const {
    return _vector == other._vector && _y_intercept == other._y_intercept;
}

double Line::calculateMagnitude() const {
    return pow(pow(_xComponent, 2) + pow(_yComponent, 2), 0.5);
}

double Line::findPointClosestTo(const cv::Point2f pointOfInterest) const {
    Vector2d toPointOfInterest(pointOfInterest.x - _startPoint.x,
                               pointOfInterest.y - _startPoint.y);

    return toPointOfInterest.scalarProjectionOnto(_vector);
}

Line Line::fromEndpoints(cv::Point2f p1, cv::Point2f p2) {
    return Line(cv::Point_<float>(), cv::Point_<float>());
}

bool Line::isParallelTo(const Line &other) const {
    return isParallelTo(other._vector);
}

bool Line::isParallelTo(const Vector2d &other) const {
    return _vector.isParallelTo(other);
}
