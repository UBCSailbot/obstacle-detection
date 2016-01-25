//
// Created by paul on 25/01/16.
//

#include "Orientation.h"

Orientation::Orientation(double rollRad, double pitchRad, double yawRad) :
    rollRadians(rollRad), pitchRadians(pitchRad), yawRadians(yawRad),
    rollDegrees(rollRad * RAD_TO_DEG), pitchDegrees(pitchRad * RAD_TO_DEG),
    yawDegrees(yawRad * RAD_TO_DEG)
{ }

std::string Orientation::toPrettyString() {
    std::ostringstream stringStream;
    stringStream << "Roll: " << rollDegrees <<
    " Pitch: " << pitchDegrees <<
    " Yaw: " << yawDegrees << std::endl;
    return stringStream.str();
}

std::string Orientation::toDataString() {
    std::ostringstream stringStream;
    stringStream << rollRadians   << " "
    << pitchRadians  << " "
    << yawRadians    << std::endl;
    return stringStream.str();
}

bool Orientation::operator==(const Orientation &other) const {
    return fabs(rollRadians - other.rollRadians) < _EPSILON &&
           fabs(pitchRadians - other.pitchRadians) < _EPSILON &&
           fabs(yawRadians - other.yawRadians) < _EPSILON;
}
