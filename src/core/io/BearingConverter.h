#ifndef OBSTACLE_DETECTION_BEARINGCONVERTER_H
#define OBSTACLE_DETECTION_BEARINGCONVERTER_H


#include <detect/DangerZone.h>

class BearingConverter {
public:
    static double relativeToAbsoluteBearing(double relativeAngle, double absoluteHeading);

    static DangerZone convertToAbsoluteBearing(DangerZone dangerZone, double bearing);

};


#endif //OBSTACLE_DETECTION_BEARINGCONVERTER_H
