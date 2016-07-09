#include "MockBoatDataStream.h"

MockBoatDataStream::MockBoatDataStream(double bearing) : _bearing(bearing) { }

CurrentData MockBoatDataStream::getBoatData() {
    CurrentData currentData;
    currentData.setBearing(_bearing);
    return currentData;
}



