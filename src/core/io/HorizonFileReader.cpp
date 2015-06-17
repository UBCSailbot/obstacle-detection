//
// Created by paul on 16/06/15.
//

#include "HorizonFileReader.h"

HorizonFileReader::HorizonFileReader(const std::string &imuLogFile,
                                     bool invertRoll, bool invertPitch) :
    _invertRoll(invertRoll), _invertPitch(invertPitch)
{
    std::ifstream infile(imuLogFile);

    float roll, pitch, yaw;

    while (infile >> roll >> pitch >> yaw)
    {
        roll = _invertRoll ? -roll : roll;
        pitch = _invertPitch ? -pitch : pitch;
        _horizons.push(Horizon(roll, pitch));
    }

    infile.close();
}

void HorizonFileReader::push(const Horizon &h) {
    _horizons.push(h);
}

Horizon HorizonFileReader::next() {
    if (_horizons.size()) {
        Horizon h = _horizons.front();
        _horizons.pop();
        return h;
    }
    else {
        throw NoSuchElementException("Tried to access from empty queue.");
    }
}