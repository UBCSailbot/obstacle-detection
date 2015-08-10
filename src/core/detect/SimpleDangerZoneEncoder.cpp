//
// Created by Aditi Chakravarthi on 15-08-09.
//

#include "SimpleDangerZoneEncoder.h"

#include <iostream>


std::vector<DangerZone> SimpleDangerZoneEncoder::identifyDangerZones(const ObstaclePositionFrame &positions,
                                                  const Horizon &horizon) const
{

    double horizonY = horizon.getEndPoint().y - horizon.getStartPoint().y;
    double horizonX = horizon.getEndPoint().x - horizon.getStartPoint().x;

    double magnitude = pow((pow(horizonX, 2) + pow(horizonY, 2)), 0.5);
    horizonX = horizonX / magnitude;
    horizonY = horizonY / magnitude;
    int centerX = positions.getCols()/2;
    int centerY = positions.getRows()/2;
    double center = (centerX - horizon.getStartPoint().x) * horizonX +
            (centerY - horizon.getStartPoint().y) * horizonY;
    std::vector<DangerZone> zones;
    double horizonFOV =  magnitude * (positions.getXFOV()/positions.getCols());

    for (std::pair<double,double> p : positions.getObstacleEdges()){
        double a =(p.first - center) / magnitude * horizonFOV;
        double b = (p.second - center) / magnitude * horizonFOV;
        DangerZone dangerZone(a, b, 0);
        zones.push_back(dangerZone);
    }


    return zones;

}

