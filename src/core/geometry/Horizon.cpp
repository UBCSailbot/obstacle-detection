//
// Created by paul on 11/05/15.
//

#include "Horizon.h"

Horizon::Horizon(cv::Point2f startPoint, cv::Point2f endPoint) :
        Line(startPoint, endPoint) {}

Horizon::Horizon(double rollRad, double pitchRad) :
        Line(cv::Point(0,0), cv::Point(0,0)) {
    setPitchRoll(pitchRad, rollRad);
}

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

/*
Check if rectangle intersect the horizon.
IN: rectangle
OUT:
RETURN: true some points in the the rectangle is above and below the horizon
 TODO: Implement this function
*/
bool Horizon::isPolyIntersect(cv::Rect rectangle) const {
    bool isAbove = false;
    bool isBelow = false;

    //add check for 4 point

    return isAbove && isBelow;
}

/*
Determine the number of pixels by which the image of the horizon is shifted.
IN:
angle_radians: pitch (forward/backward) angle of boat. Backward pitch (looking up, horizon at bottom) is positive.

OUT:
RETURN:
pixel_shift: 0 when horizon centred, +height/2 when horizon at top, -height/2 at bottom.
May exceed magnitude height/2 for large angles.
*/
double Horizon::pitchHorizonPixelShift(double angle){
    return angle / ((double) VIEWPORT_FOV_DEGREES_VERTICAL * M_PI / 180.0) * (double) VIEWPORT_HEIGHT_PIX;
}

/*
Determine the number of pixels by which the image of the horizon is differentially shifted.
When the boat is rolled left (positive tilt), the horizon appears higher in the image on the left side than on the right.
IN:
angle_radians: roll (left/right) angle of boat. Left roll (horizon high on left side) is positive.

OUT:
RETURN:
pixel_shift: 0 when horizon centred, +height/2 when horizon from top left to bottom right.
May exceed magnitude height/2 for large angles.
*/
double Horizon::rollHorizonPixelShift(double angle) {
    return tan(angle) * (double) VIEWPORT_WIDTH_PIX / 2.0;
}

/*
Convert pitch and roll angles to intersection points.
PRE: pitch, roll angles in radians given
POST: pitch, roll, and intersection heights stored in class.
*/
void Horizon::setPitchRoll(double pitch, double roll) {
    double pitchShift = pitchHorizonPixelShift(pitch);
    heightLeft = (int) (pitchShift + VIEWPORT_HEIGHT_PIX / 2);
    heightRight = (int) (pitchShift + VIEWPORT_HEIGHT_PIX / 2);

    double rollShift = rollHorizonPixelShift(roll);
    // NOTE: The two signs below have been flipped from their original states to invert the roll axis of the IMU. If the IMU configuration changes and this is no longer necessary, feel free to switch them back.
    heightLeft -= rollShift;
    heightRight += rollShift;

    // XXX: Assumes that the horizon intersects both
    //  vertical edges of the frame
    _startPoint = cv::Point2f(0, heightLeft);
    _endPoint = cv::Point2f(VIEWPORT_WIDTH_PIX, heightRight);
}
