//
// Created by paul on 10/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_MOC_IMU_H
#define OBSTACLE_AVOIDANCE_MOC_IMU_H

#include "RTIMULib.h"
#include <RTIMULibDefs.h>
#include <sstream>

#include <thread>
#include <string>

class moc_IMU {

public:
    moc_IMU();
    ~moc_IMU();

    double getRollDeg();
    double getPitchDeg();
    double getYawDeg();

    std::string toString();

private:

    std::thread imuThread;

    void start();

    double mockRoll;
    double mockPitch;
    double mockYaw;
};


#endif //OBSTACLE_AVOIDANCE_MOC_IMU_H
