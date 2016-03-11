//
// Created by paul on 08/08/15.
//

#ifndef OBSTACLE_AVOIDANCE_DANGERZONEENCODER_H
#define OBSTACLE_AVOIDANCE_DANGERZONEENCODER_H

#include "features/ObstaclePositionFrame.h"
#include "detect/DangerZone.h"
#include <vector>
#include <math.h>
#include "geometry/Horizon.h"


/**
 * Interface for objects that convert obstacle sightings into DangerZones.
 */
class DangerZoneEncoder {

  public:

    /**
     * Takes in an ObstaclePositionFrame, which contains an image, a horizon line,
     *  camera specs, and a series of obstacles encoded as vectors of points.
     *
     * Outputs a list of relative headings, where each obstacle is ascribed a pair
     *  of headings: one that designates its port-most edge, the other its starboard-
     *  most edge.
     */
    virtual std::vector <DangerZone> identifyDangerZones(const ObstaclePositionFrame &positions)
        const = 0;

};

#endif //OBSTACLE_AVOIDANCE_DANGERZONEENCODER_H
