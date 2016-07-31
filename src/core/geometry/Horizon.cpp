//
// Created by paul on 11/05/15.
//

#include "Horizon.h"

Horizon::Horizon(cv::Point2f startPoint, cv::Point2f endPoint) :
        Line(startPoint, endPoint) {}

/*
Check if given point is above horizon.
IN: point of interest
OUT:
RETURN: true if point is above horizon
*/
bool Horizon::isPointAbove(cv::Point2f pointOfInterest) const {
    return isPointAbove(pointOfInterest.x, pointOfInterest.y);
}

bool Horizon::isPointAbove(const float &x, const float &y) const {
    if (y > _startPoint.y && y > _endPoint.y)
        return false;

    if (y < _startPoint.y && y < _endPoint.y)
        return true;

    return (_endPoint.x - _startPoint.x) * (y - _startPoint.y) <
           (_endPoint.y - _startPoint.y) * (x - _startPoint.x);

}


bool Horizon::isRectAbove(cv::Rect rectangle) const {
    return isPointAbove(rectangle.tl()) &&
           isPointAbove(rectangle.br()) &&
           isPointAbove(cv::Point2f(rectangle.x + rectangle.width, rectangle.y)) &&
           isPointAbove(cv::Point2f(rectangle.x, rectangle.y + rectangle.height));
}
