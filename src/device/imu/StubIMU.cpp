#include "StubIMU.h"

StubIMU::StubIMU(double mockRoll, double mockPitch, double mockYaw) : _mockPitch(mockPitch), _mockYaw(mockYaw), _mockRoll(mockRoll) {

}

Orientation StubIMU::getOrientation() {
 return Orientation(_mockRoll, _mockPitch,_mockYaw);
}



