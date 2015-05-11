//
// Created by paul on 09/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_IMU_H
#define OBSTACLE_AVOIDANCE_IMU_H

#include "RTIMULib.h"
#include <RTIMULibDefs.h>
#include <sstream>

#include <thread>
#include <string>

class IMU {

public:
    IMU();
    ~IMU();

    double getRollDeg();
    double getPitchDeg();
    double getYawDeg();

    std::string toString();

private:
    RTIMU *imu;
    RTIMU_DATA imuData;

    std::thread imuThread;

    void startCapture();

};


#endif //OBSTACLE_AVOIDANCE_IMU_H
