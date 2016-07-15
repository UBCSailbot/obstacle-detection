#ifndef OBSTACLE_AVOIDANCE_PARALLELIMU_H
#define OBSTACLE_AVOIDANCE_PARALLELIMU_H


#include <thread>

#include <RTIMULibDefs.h>
#include <mutex>
#include "RTIMULib.h"

#include "IMU.h"
#include "paths/Resources.h"

class ParallelIMU: public IMU {

  public:
    ParallelIMU();

    Orientation getOrientation() override;

    // TODO: These are not currently being used anywhere.
    // Move them to a configuration section.
    static constexpr double ROLL_ADJUST = 0.09;
    static constexpr double PITCH_ADJUST = 0.15;

  private:
    RTIMU *imu_;
    RTIMU_DATA imuData_;
    std::mutex lock_;
    std::thread imuThread_;

    void startCapture();

};


#endif //OBSTACLE_AVOIDANCE_PARALLELIMU_H
