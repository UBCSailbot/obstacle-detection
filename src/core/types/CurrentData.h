#ifndef ROUTEMAKING_CURRENTDATA_H
#define ROUTEMAKING_CURRENTDATA_H


/**
 * A class that contains telemetry data about Ada. It may be subsumed by the more generic Boat class not yet in master.
 */
class CurrentData {
 public:
  double speed_over_ground() { return speed_over_ground_; };
  double bearing() { return bearing_; };

  void setSpeedOverGround(double speed_over_ground) { speed_over_ground_ = speed_over_ground; };
  void setBearing(double bearing) { bearing_ = bearing; };

 private:
  double speed_over_ground_, bearing_;
};


#endif //ROUTEMAKING_CURRENTDATA_H
