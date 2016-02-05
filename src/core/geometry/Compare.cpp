//
// Created by paul on 31/01/16.
//

#include "Compare.h"

bool Compare::areAnglesEqual(double angle1, double angle2) {
    if (angle1 == angle2) {
        return true;
    }

    // Assume angles are between -2*pi and 2*pi
    // Degree of granularity we care about is 0.5 deg, or pi / 360 rad
    return fabs(angle1 - angle2) < ANGLE_PRECISION_RAD;

}

bool Compare::areCoordinatesEqual(double coord1, double coord2) {
    return fabs(coord1 - coord2) < COORDINATE_PRECISION;
}

bool Compare::areMagnitudesEqual(double mag1, double mag2) {
    return fabs(mag1 - mag2) < MAGNITUDE_PRECISION;
}
