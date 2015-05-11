//
// Created by paul on 10/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_PARALLELIMU_H
#define OBSTACLE_AVOIDANCE_PARALLELIMU_H

#include "RTIMULib.h"
#include "IMU.h"
#include <RTIMULibDefs.h>

#include <thread>

class ParallelIMU : public IMU {

public:
    ParallelIMU();
    ~ParallelIMU();

    double getRollDeg();
    double getPitchDeg();
    double getYawDeg();

private:
    RTIMU *imu;
    RTIMU_DATA imuData;

    std::thread imuThread;

    void startCapture();

};


#endif //OBSTACLE_AVOIDANCE_PARALLELIMU_H
