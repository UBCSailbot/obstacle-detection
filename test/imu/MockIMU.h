//
// Created by paul on 10/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_MOC_IMU_H
#define OBSTACLE_AVOIDANCE_MOC_IMU_H

#include "RTIMULib.h"
#include "../../src/imu/IMU.h"
#include <RTIMULibDefs.h>
#include <sstream>

#include <thread>
#include <string>

class MockIMU : public IMU {

public:
    MockIMU();
    ~MockIMU();

private:

    std::thread imuThread;

    void startCapture();

    double mockRoll;
    double mockPitch;
    double mockYaw;

    double getRollDeg();
    double getPitchDeg();
    double getYawDeg();

    double getRollRad();
    double getPitchRad();
    double getYawRad();
};


#endif //OBSTACLE_AVOIDANCE_MOC_IMU_H
