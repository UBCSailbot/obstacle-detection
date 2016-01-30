//
// Created by paul on 16/06/15.
//

#include "OrientationFileReader.h"

OrientationFileReader::OrientationFileReader(const std::string &imuLogFile,
                                             bool invertRoll, bool invertPitch) :
    _invertRoll(invertRoll), _invertPitch(invertPitch)
{
    std::ifstream infile(imuLogFile);

    float roll, pitch, yaw;

    while (infile >> roll >> pitch >> yaw)
    {
        roll = _invertRoll ? -roll : roll;
        pitch = _invertPitch ? -pitch : pitch;
        Orientation o(roll, pitch, yaw);
        _orientations.push(o);
    }

    infile.close();
}

void OrientationFileReader::push(const Orientation &o) {
    _orientations.push(o);
}

Orientation OrientationFileReader::next() {
    if (_orientations.size()) {
        Orientation o = _orientations.front();
        _orientations.pop();
        return o;
    }
    else {
        throw NoSuchElementException("Tried to access from empty queue.");
    }
}