#include "CurrentDataDeserializer.h"

/**
 * @param inputCurrentData - " (double)bearing (double)speedOverGround"
 */
CurrentData CurrentDataDeserializer::deserialize(std::string inputCurrentData) {
    CurrentData currentData;
    char *pEnd;
    double latitude = strtod(inputCurrentData.c_str(), &pEnd);
    double longitude = strtod(pEnd, &pEnd);
    double bearing = strtod(pEnd, &pEnd);
    double speedOverGround = strtod(pEnd, NULL);

    currentData.setSpeedOverGround(speedOverGround);
    currentData.setHeading(bearing);
    currentData.setLatitude(latitude);
    currentData.setLongitude(longitude);

    return currentData;
}