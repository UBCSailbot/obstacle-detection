//
// Created by Aditi Chakravarthi on 15-08-09.
//

#ifndef OBSTACLE_AVOIDANCE_SIMPLEDANGERZONEENCODER_H
#define OBSTACLE_AVOIDANCE_SIMPLEDANGERZONEENCODER_H

#include "../geometry/Horizon.h"
#include "ObstaclePositionFrame.h"
#include "DangerZone.h"
#include "DangerZoneEncoder.h"

class SimpleDangerZoneEncoder: public DangerZoneEncoder {

public:



    std::vector<DangerZone> identifyDangerZones(const ObstaclePositionFrame &positions,
                                                              const Horizon &horizon) const;

private:
};


#endif //OBSTACLE_AVOIDANCE_SIMPLEDANGERZONEENCODER_H
