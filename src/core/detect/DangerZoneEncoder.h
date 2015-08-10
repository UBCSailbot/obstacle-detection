//
// Created by paul on 08/08/15.
//

#ifndef OBSTACLE_AVOIDANCE_DANGERZONEENCODER_H
#define OBSTACLE_AVOIDANCE_DANGERZONEENCODER_H



#include "detect/ObstaclePositionFrame.h"
#include "detect/DangerZone.h"
#include <vector>
#include <math.h>
#include "../geometry/Horizon.h"




/**
 * Interface for objects that convert obstacle sightings into DangerZones.
 */
class DangerZoneEncoder {

public:

    virtual const std::vector<DangerZone> identifyDangerZones(const ObstaclePositionFrame &positions,
                                                 const Horizon &horizon)=0;

};

#endif //OBSTACLE_AVOIDANCE_DANGERZONEENCODER_H
