//
// Created by paul on 09/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_IMU_H
#define OBSTACLE_AVOIDANCE_IMU_H

#include <sstream>
#include <string>

class IMU {

public:
    virtual double getRollDeg() = 0;
    virtual double getPitchDeg() = 0;
    virtual double getYawDeg() = 0;

    virtual double getRollRad() = 0;
    virtual double getPitchRad() = 0;
    virtual double getYawRad() = 0;

    /**
     * Returns a relatively nicely-formatted string with roll, pitch, and yaw in degrees.
     */
    virtual std::string toPrettyString();

    /**
     * Returns a space-efficient string with roll, pitch, and yaw in radians.
     */
    virtual std::string toDataString();

private:
    std::ostringstream stringStream;

    void resetStringStream();
};


#endif //OBSTACLE_AVOIDANCE_IMU_H
