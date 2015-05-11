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

    virtual std::string toPrettyString();
    virtual std::string toDataString();

private:
    std::ostringstream stringStream;

    void resetStringStream();
};


#endif //OBSTACLE_AVOIDANCE_IMU_H
