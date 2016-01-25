//
// Created by paul on 11/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_HORIZON_H
#define OBSTACLE_AVOIDANCE_HORIZON_H


#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <cmath>
#include <math.h>

#include "camera/lepton/LeptonCameraSpecifications.h"
#include "Line.h"

class Horizon : public Line {

public:
    Horizon(cv::Point2f startPoint, cv::Point2f endPoint);

    /*
    Check if given point is above horizon.
    IN: point of interest
    OUT:
    RETURN: true if point is above horizon
    */
    bool isPointAbove(cv::Point2f pointOfInterest) const;
    bool isPointAbove(const float &x, const float &y) const;

    /*
    Check if rectangle intersect the horizon.
    IN: rectangle
    OUT:
    RETURN: true some points in the the rectangle is above and below the horizon
    */
    bool isPolyIntersect(cv::Rect rectangle) const;

private:
    // Store the height of the intersection of the horizon with the edges of the viewport
    int heightLeft, heightRight;

    /* Convert pitch and roll angles to intersection points.
     * PRE: pitch, roll angles in radians given
     * POST: pitch, roll, and intersection heights stored in class.
     */
    void setPitchRoll(double pitch, double roll);

    /*
    Determine the number of pixels by which the image of the horizon is shifted.
    IN:
    angle_radians: pitch (forward/backward) angle of boat. Backward pitch (looking up, horizon at bottom) is positive.

    OUT:
    RETURN:
    pixel_shift: 0 when horizon centred, +height/2 when horizon at top, -height/2 at bottom.
    May exceed magnitude height/2 for large angles.
    */
    double pitchHorizonPixelShift(double angle);

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
    double rollHorizonPixelShift(double angle);
};

#endif //OBSTACLE_AVOIDANCE_HORIZON_H
