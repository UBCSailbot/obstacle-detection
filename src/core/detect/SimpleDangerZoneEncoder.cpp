//
// Created by paul
//

#include "SimpleDangerZoneEncoder.h"

#include <iostream>


SimpleDangerZoneEncoder::SimpleDangerZoneEncoder(ICameraSpecifications specs) :
        _cameraSpecs(specs)
{
    _pixToDegMultiplier = _cameraSpecs.FOVDegreesHorizontal / _cameraSpecs.pixelWidth;
}

double SimpleDangerZoneEncoder::calculateDistanceFromCenterLine(Line centerLine, cv::Point2d p)const {
    cv::Point2d normalizedCenterLine(centerLine.getEndPoint().x - centerLine.getStartPoint().x,
                                     centerLine.getEndPoint().y - centerLine.getStartPoint().y);
    cv::Point2d normalizedPoint(p.x - centerLine.getStartPoint().x,
                                p.y - centerLine.getStartPoint().y);

    double numerator = normalizedPoint.x * normalizedCenterLine.y -
            normalizedPoint.y * normalizedCenterLine.x;
    double denominator = centerLine.getMagnitude();

    return numerator / denominator;
}

std::vector<DangerZone> SimpleDangerZoneEncoder::identifyDangerZones(
        const ObstaclePositionFrame &obstacleFrame,
        const Horizon &horizon) const
{
    Line centerLine = findCenterLine(obstacleFrame, horizon);
    std::vector<DangerZone> zones;

    for (Obstacle o : obstacleFrame.getObstacles()) {
        double portDistance = calculateDistanceFromCenterLine(centerLine, o.getPortmostVertex());
        double starboardDistance = calculateDistanceFromCenterLine(centerLine, o.getStarboardmostVertex());
        DangerZone dz(portDistance * _pixToDegMultiplier, starboardDistance * _pixToDegMultiplier, 0);
        zones.push_back(dz);
    }

    return zones;

}

Line SimpleDangerZoneEncoder::findCenterLine(ObstaclePositionFrame frame, Horizon h) const {
    cv::Point2d normalizedHorizon(h.getEndPoint().x - h.getStartPoint().x,
                                  h.getEndPoint().y - h.getStartPoint().y);

    cv::Point2d normalToHorizon(-normalizedHorizon.y, normalizedHorizon.x);

    cv::Point2f centerOfFrame(frame.getFrameWidth() / 2, frame.getFrameHeight() / 2);
    return Line(centerOfFrame, cv::Point2d(centerOfFrame.x + normalToHorizon.x,
                                           centerOfFrame.y + normalToHorizon.y) );
}