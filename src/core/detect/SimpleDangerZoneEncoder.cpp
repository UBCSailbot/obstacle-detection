//
// Created by paul
//

#include "SimpleDangerZoneEncoder.h"


SimpleDangerZoneEncoder::SimpleDangerZoneEncoder() {

}

double SimpleDangerZoneEncoder::calculateDistanceFromCenterLine(Line centerLine, cv::Point2d p) const {
    cv::Point2d normalizedCenterLine(centerLine.getEndPoint().x - centerLine.getStartPoint().x,
                                     centerLine.getEndPoint().y - centerLine.getStartPoint().y);
    cv::Point2d normalizedPoint(p.x - centerLine.getStartPoint().x,
                                p.y - centerLine.getStartPoint().y);

    double numerator = normalizedPoint.x * normalizedCenterLine.y -
                       normalizedPoint.y * normalizedCenterLine.x;
    double denominator = centerLine.calculateMagnitude();

    return numerator / denominator;
}

std::vector<DangerZone> SimpleDangerZoneEncoder::identifyDangerZones(
        const ObstaclePositionFrame &obstacleFrame)  {
    auto cameraSpecs = obstacleFrame.getCameraSpec();
    double pixToDegMultiplier = cameraSpecs.FOVDegreesHorizontal / cameraSpecs.pixelWidth;
    Line centerLine = obstacleFrame.calculateCenterLine();
    std::vector<DangerZone> zones;

    for (const Obstacle &obstacle : obstacleFrame.getObstacles()) {
        double portDistance = calculateDistanceFromCenterLine(centerLine, obstacle.getPortmostVertex());
        double starboardDistance = calculateDistanceFromCenterLine(centerLine, obstacle.getStarboardmostVertex());
        DangerZone dz(portDistance * pixToDegMultiplier, starboardDistance * pixToDegMultiplier, 0);
        zones.push_back(dz);
    }

    return zones;

}
