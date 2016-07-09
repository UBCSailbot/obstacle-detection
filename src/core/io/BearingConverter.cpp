#include <math.h>
#include "BearingConverter.h"

double BearingConverter::relativeToAbsoluteBearing(double relativeAngle, double absoluteHeading) {

    double absoluteAngle = relativeAngle + absoluteHeading;

    if (absoluteAngle < 0) {
        absoluteAngle = fmod(absoluteAngle, -360.0);
    } else {
        absoluteAngle = fmod(absoluteAngle, 360.0);
    }

    if (absoluteAngle <= -180) {
        absoluteAngle = absoluteAngle + 360;
    } else if (absoluteAngle > 180) {
        absoluteAngle = absoluteAngle - 360;
    }

    return absoluteAngle;
}

DangerZone BearingConverter::convertToAbsoluteBearing(DangerZone dangerZone, double bearing) {
    double convertedPortAngle = relativeToAbsoluteBearing(dangerZone.getPortAngleDeg(), bearing);
    double convertedStarboardAngle = relativeToAbsoluteBearing(dangerZone.getStarboardAngleDeg(), bearing);

    DangerZone convertedDangerZone(convertedPortAngle, convertedStarboardAngle, dangerZone.getLateralOffsetMeters());
    return convertedDangerZone;
}
