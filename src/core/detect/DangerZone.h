//
// Created by paul on 08/08/15.
//

#ifndef OBSTACLE_AVOIDANCE_DANGERZONE_H
#define OBSTACLE_AVOIDANCE_DANGERZONE_H

/**
 * Represents a triangular area on the idealized 2D surface of the
 *  water, within which an obstacle is thought to lie.
 *
 * This triangular region is defined relative to the boat's heading
 *  at the time that obstacle detection is performed.
 */
class DangerZone {

public:

    DangerZone(double portAngleDeg, double starboardAngleDeg, double lateralOffsetMeters) :
            _portAngleDeg(portAngleDeg), _starboardAngleDeg(starboardAngleDeg),
            _lateralOffsetMeters(lateralOffsetMeters)
    {    }

    /**
     * Returns the distance, in degrees, of the left-most edge of the
     *  danger zone from the current heading.
     */
    const float getPortAngleDeg() const {
        return _portAngleDeg;
    }

    /**
     * Returns the distance, in degrees, of the right-most edge of the
     *  danger zone from the current heading.
     */
    const float getStarboardAngleDeg() const {
        return _starboardAngleDeg;
    }

    /**
     * If the boat has a non-zero roll angle and the obstacle sensor is at a
     *  non-negligible radial distance from the boat's axis of rotation,
     *  the sensor experiences a lateral translation that correspondingly
     *  shifts the apparent heading of the boat at that moment.
     *
     * This function returns that lateral offset, in meters.
     */
    const float getLateralOffsetMeters() const {
        return _lateralOffsetMeters;
    }

private:
    const float _portAngleDeg;
    const float _starboardAngleDeg;
    const float _lateralOffsetMeters;

};


#endif //OBSTACLE_AVOIDANCE_DANGERZONE_H
