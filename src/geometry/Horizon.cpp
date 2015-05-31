//
// Created by paul on 11/05/15.
//

#include "Horizon.h"

#ifndef UNIX
    #define M_PI		3.14159265358979323846
#endif

Horizon::Horizon(double roll, double pitch) : roll(roll), pitch(pitch) {
    setPitchRoll(pitch, roll);
}

Horizon::~Horizon() {
}

cv::Point2f Horizon::getStart() const {
    return start;
}


cv::Point2f Horizon::getEnd() const {
    return end;
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
    if (y > start.y && y > end.y)
        return false;

    if (y < start.y && y < end.y)
        return true;

    return (end.x - start.x) * (y - start.y) < (end.y - start.y) * (x - start.x);

}

/*
Check if rectangle intersect the horizon.
IN: rectangle
OUT:
RETURN: true some points in the the rectangle is above and below the horizon
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
    return -tan(angle) * (double) VIEWPORT_WIDTH_PIX / 2.0;
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
    heightLeft += rollShift;
    heightRight -= rollShift;

    // XXX: Assumes that the horizon intersects both
    //  vertical edges of the frame
    start = cv::Point2f(0, heightLeft);
    end = cv::Point2f(VIEWPORT_WIDTH_PIX, heightRight);
}

