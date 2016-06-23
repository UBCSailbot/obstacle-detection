#ifndef OBSTACLE_DETECTION_STUBIMU_H
#define OBSTACLE_DETECTION_STUBIMU_H


#include "IMU.h"

class StubIMU : public IMU {
public:
    StubIMU(double _mockRoll, double _mockPitch, double _mockYaw);

    Orientation getOrientation() override;

private:
    double _mockRoll;
    double _mockPitch;
    double _mockYaw;
};

#endif //OBSTACLE_DETECTION_STUBIMU_H
