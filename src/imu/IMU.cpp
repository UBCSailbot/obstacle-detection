//
// Created by paul on 09/05/15.
//

#include "IMU.h"

std::string IMU::toPrettyString() {
    resetStringStream();
    stringStream << "Roll: " << getRollDeg() <<
                    " Pitch: " << getPitchDeg() <<
                    " Yaw: " << getYawDeg() << std::endl;
    return stringStream.str();
}

std::string IMU::toDataString() {
    resetStringStream();
    stringStream << getRollDeg()   << " "
                 << getPitchDeg()  << " "
                 << getYawDeg()    << std::endl;
    return stringStream.str();
}

void IMU::resetStringStream() {
    stringStream.str("");
    stringStream.clear();
}