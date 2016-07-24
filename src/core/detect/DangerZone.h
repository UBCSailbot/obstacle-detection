#ifndef OBSTACLE_AVOIDANCE_DANGERZONE_H
#define OBSTACLE_AVOIDANCE_DANGERZONE_H

#include <chrono>

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
            _lateralOffsetMeters(lateralOffsetMeters) {}

    /**
     * Returns the distance, in degrees, of the left-most edge of the
     *  danger zone from the current heading.
     */
    double getPortAngleDeg() const {
        return _portAngleDeg;
    }

    /**
     * Returns the distance, in degrees, of the right-most edge of the
     *  danger zone from the current heading.
     */
    double getStarboardAngleDeg() const {
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
    double getLateralOffsetMeters() const {
        return _lateralOffsetMeters;
    }

    double getWidthDegrees() const {
        return _starboardAngleDeg - _portAngleDeg;
    }

    double get_latitude() const {
        return _latitude;
    }

    void set_latitude(double _latitude) {
        DangerZone::_latitude = _latitude;
    }

    double get_longitude() const {
        return _longitude;
    }

    void set_longitude(double _longitude) {
        DangerZone::_longitude = _longitude;
    }

    const std::chrono::duration<uint64_t, std::ratio<1, 1>> &getTime() const {
        return time;
    }

    void setTime(const std::chrono::duration<uint64_t, std::ratio<1, 1>> &time) {
        DangerZone::time = time;
    }

private:
    double _portAngleDeg;
    double _starboardAngleDeg;
    double _lateralOffsetMeters;

    double _latitude, _longitude;

    std::chrono::duration<uint64_t> time;
};


#endif //OBSTACLE_AVOIDANCE_DANGERZONE_H
