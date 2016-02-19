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

Orientation MockIMU::getOrientation() {
    return Orientation(mockRoll, mockPitch, mockYaw);
}
