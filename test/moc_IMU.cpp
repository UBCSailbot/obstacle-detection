//
// Created by paul on 10/05/15.
//

#include "moc_IMU.h"

moc_IMU::moc_IMU() {

    // initialize dummies
    mockPitch = 0;
    mockRoll = 0;
    mockYaw = 0;

    std::thread tempThread(&moc_IMU::start, this);
    std::swap(tempThread, imuThread);

}

void moc_IMU::start() {
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

moc_IMU::~moc_IMU() {

}

double moc_IMU::getRollDeg() {
    return mockRoll;
}

double moc_IMU::getPitchDeg() {
    return mockPitch;
}

double moc_IMU::getYawDeg() {
    return mockYaw;
}

std::string moc_IMU::toString() {
    std::ostringstream stringStream;
    stringStream << "Roll: " << getRollDeg() <<
    " Pitch: " << getPitchDeg() <<
    " Yaw: " << getYawDeg() << std::endl;
    return stringStream.str();
}