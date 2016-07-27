#include "MockBoatDataStream.h"

MockBoatDataStream::MockBoatDataStream() : MockBoatDataStream(DEFAULT_MOCK_HEADING) { }

MockBoatDataStream::MockBoatDataStream(double heading) : heading_(heading) { }

CurrentData MockBoatDataStream::getBoatData() {
    CurrentData currentData;
    currentData.setHeading(heading_);
    return currentData;
}



