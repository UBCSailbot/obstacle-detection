//
// Created by paul on 30/05/15.
//

#include "Line.h"

Line::Line(const cv::Point2f startPoint, const cv::Point2f endPoint) :
    _startPoint(startPoint), _endPoint(endPoint)
    {
        _xComponent = _endPoint.x - _startPoint.x;
        _yComponent = _endPoint.y - _startPoint.y;
    }

cv::Point2f Line::getStartPoint() const {
    return _startPoint;
}

cv::Point2f Line::getEndPoint() const {
    return _endPoint;
}

bool Line::operator==(const Line &other) const {
    const int EPSILON_FACTOR = 1000;
    return (_startPoint.x - other._startPoint.x <= _startPoint.x / EPSILON_FACTOR) &&
            (_startPoint.y - other._startPoint.y <= _startPoint.y / EPSILON_FACTOR) &&
            (_endPoint.x - other._endPoint.x <= _endPoint.x / EPSILON_FACTOR) &&
            (_endPoint.y - other._endPoint.y <= _endPoint.y / EPSILON_FACTOR);
}

double Line::getMagnitude() {
    if (!_magnitudeCalculated) {
        _magnitude = pow( pow(_xComponent, 2) + pow(_yComponent, 2), 0.5);
        _magnitudeCalculated = true;
    }
    return _magnitude;
}


double Line::projectPointOnto(const cv::Point2f pointOfInterest) const {
    double vectorx = pointOfInterest.x - _startPoint.x;
    double vectory = pointOfInterest.y - _startPoint.y;

    return scalarProjectAontoB(vectorx, vectory, _xComponent, _yComponent);
}