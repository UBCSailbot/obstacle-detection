//
// Created by paul on 10/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_MOC_IMU_H
#define OBSTACLE_AVOIDANCE_MOC_IMU_H

#include <sstream>
#include <thread>
#include <string>

#include <RTIMULib.h>
#include <RTIMULibDefs.h>

#include "imu/IMU.h"


class MockIMU : public IMU {

public:
    MockIMU();

    virtual Orientation getOrientation() override;

private:

    std::thread imuThread;

    void startCapture();

    double mockRoll;
    double mockPitch;
    double mockYaw;
};


#endif //OBSTACLE_AVOIDANCE_MOC_IMU_H
