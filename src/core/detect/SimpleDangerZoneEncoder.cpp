//
// Created by Aditi Chakravarthi on 15-08-09.
//

#include "SimpleDangerZoneEncoder.h"

#include <iostream>


std::vector<DangerZone> SimpleDangerZoneEncoder::identifyDangerZones(
                                                const ObstaclePositionFrame &obstacleFrame,
                                                const Horizon &horizon) const
{

    double horizonY = horizon.getEndPoint().y - horizon.getStartPoint().y;
    double horizonX = horizon.getEndPoint().x - horizon.getStartPoint().x;

    double magnitude = pow((pow(horizonX, 2) + pow(horizonY, 2)), 0.5);
    horizonX = horizonX / magnitude;
    horizonY = horizonY / magnitude;
    int centerX = obstacleFrame.getFrameWidth() / 2;
    int centerY = obstacleFrame.getFrameHeight() / 2;
    double center = (centerX - horizon.getStartPoint().x) * horizonX +
            (centerY - horizon.getStartPoint().y) * horizonY;
    std::vector<DangerZone> zones;
    double multiplier = obstacleFrame.getXFOV() / obstacleFrame.getFrameWidth();

//    for (std::pair<double,double> p : obstacleFrame.getObstacles()){
//        double a = (p.first - center)  * multiplier;
//        double b = (p.second - center) * multiplier;
//        DangerZone dangerZone(a, b, 0);
//        zones.push_back(dangerZone);
//    }

    return zones;

}

double calculateDistanceFromCenterLine(double centerX, double centerY,
                                        double horizonX, double horizonY,
                                        double pointX, double pointY)
{
    double newBasisX = pointX - centerX;
    double newBasisY = pointY - centerY;

    double dotProduct = newBasisX * horizonX + newBasisY * horizonY;
    double vectorMagnitude = pow((pow(newBasisX, 2) + pow(newBasisY, 2)), 0.5);

    return dotProduct / vectorMagnitude;
}

std::vector<DangerZone> SimpleDangerZoneEncoder::identifyDangerZones2(
        const ObstaclePositionFrame &obstacleFrame,
        const Horizon &horizon) const
{

    double horizonY = horizon.getEndPoint().y - horizon.getStartPoint().y;
    double horizonX = horizon.getEndPoint().x - horizon.getStartPoint().x;
    double horizonLength = pow((pow(horizonX, 2) + pow(horizonY, 2)), 0.5);

    int centerX = obstacleFrame.getFrameWidth() / 2;
    int centerY = obstacleFrame.getFrameHeight() / 2;

    double pixToDegMultiplier = 0.6281;

    std::vector<DangerZone> zones;
    double horizonFOV = horizonLength * (obstacleFrame.getXFOV() / obstacleFrame.getFrameWidth());

    for (Obstacle obstacle : obstacleFrame.getObstacles())
    {
        double a = calculateDistanceFromCenterLine(centerX, centerY, horizonX, horizonY,
                                                   obstacle.getPortmostVertex(horizon).x,
                                                   obstacle.getPortmostVertex(horizon).y);

        double b = calculateDistanceFromCenterLine(centerX, centerY, horizonX, horizonY,
                                                   obstacle.getPortmostVertex(horizon).x,
                                                   obstacle.getPortmostVertex(horizon).y);

        //DangerZone dangerZone(a, b, 0);
        //zones.push_back(dangerZone);
    }

    return zones;

}

