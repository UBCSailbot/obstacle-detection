#ifndef OBSTACLE_AVOIDANCE_CURRENTDATA_H
#define OBSTACLE_AVOIDANCE_CURRENTDATA_H


/**
 * A class that contains telemetry data about Ada. It may be subsumed by the more generic Boat class not yet in master.
 */
class CurrentData {
public:

    double speed_over_ground() const { return speed_over_ground_; };

    double heading() const { return heading_; };

    double latitude() const { return latitude_; };

    double longitude() const { return longitude_; };

    void setSpeedOverGround(double speed_over_ground) { speed_over_ground_ = speed_over_ground; };

    void setHeading(double heading) { heading_ = heading; };

    void setLatitude(double latitude) { latitude_ = latitude; };

    void setLongitude(double longitude) { longitude_ = longitude; };

private:
    double speed_over_ground_, heading_, latitude_, longitude_;
};


#endif //OBSTACLE_AVOIDANCE_CURRENTDATA_H
