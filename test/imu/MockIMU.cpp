//
// Created by paul on 10/05/15.
//

#include "MockIMU.h"

MockIMU::MockIMU() {

    // initialize dummies
    mockPitch = 0;
    mockRoll = 0;
    mockYaw = 0;

    std::thread tempThread(&MockIMU::startCapture, this);
    std::swap(tempThread, imuThread);

}

void MockIMU::startCapture() {
    //  now just process data
    while (1) {
        //  poll at a manageable rate
        usleep(100);

        // fetch dummy data
        mockPitch++;
        mockRoll++;
        mockYaw++;
    }
}

MockIMU::~MockIMU() {

}

double MockIMU::getRollDeg() {
    return mockRoll;
}

double MockIMU::getPitchDeg() {
    return mockPitch;
}

double MockIMU::getYawDeg() {
    return mockYaw;
}

double MockIMU::getRollRad() {
    return mockRoll;
}

double MockIMU::getPitchRad() {
    return mockPitch;
}

double MockIMU::getYawRad() {
    return mockYaw;
}
