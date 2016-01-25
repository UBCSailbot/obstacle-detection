//
// Created by paul on 17/01/16.
//

#ifndef OBSTACLE_DETECTION_HORIZONFACTORY_H
#define OBSTACLE_DETECTION_HORIZONFACTORY_H


#include "Horizon.h"
#include "Orientation.h"
#include "camera/ICameraSpecifications.h"

class HorizonFactory {

public:

    HorizonFactory(ICameraSpecifications specs);

    /*
    Convert pitch and roll angles to intersection points.
    PRE: pitch, roll angles in radians given
    POST: pitch, roll, and intersection heights stored in class.
    */
    Horizon makeHorizon(Orientation o) const;

    /**
     * Makes a level horizon that passes through the middle
     *  of the image, as if it had been produced with 0 pitch
     *  and 0 roll.
     */
    Horizon makeNeutralHorizon() const;

private:
    ICameraSpecifications _cameraSpecs;

    /*
    Determine the number of pixels by which the image of the horizon is shifted.
    IN:
    angle_radians: pitch (forward/backward) angle of boat. Backward pitch (looking up, horizon at bottom) is positive.

    OUT:
    RETURN:
    pixel_shift: 0 when horizon centred, +height/2 when horizon at top, -height/2 at bottom.
    May exceed magnitude height/2 for large angles.
    */
    double pitchHorizonPixelShift(double angle, ICameraSpecifications spec) const;

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
    double rollHorizonPixelShift(double angle, ICameraSpecifications spec) const;
};


#endif //OBSTACLE_DETECTION_HORIZONFACTORY_H
