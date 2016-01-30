//
// Created by paul on 25/01/16.
//

#include "Orientation.h"

const double Orientation::RAD_TO_DEG = 180 / M_PI;

const double Orientation::_EPSILON = 0.0001;

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
    return std::abs(rollRadians - other.rollRadians) < _EPSILON &&
           std::abs(pitchRadians - other.pitchRadians) < _EPSILON &&
           std::abs(yawRadians - other.yawRadians) < _EPSILON;
}
