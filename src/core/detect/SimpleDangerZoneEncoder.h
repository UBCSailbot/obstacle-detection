//
// Created by Aditi Chakravarthi on 15-08-09.
//

#ifndef OBSTACLE_AVOIDANCE_SIMPLEDANGERZONEENCODER_H
#define OBSTACLE_AVOIDANCE_SIMPLEDANGERZONEENCODER_H

#include <iostream>

#include "geometry/Horizon.h"
#include "features/ObstaclePositionFrame.h"
#include "DangerZone.h"
#include "DangerZoneEncoder.h"

/**
 * Works under the following assumptions:
 *
 *  (1) The vector pointing "straight ahead", that is, the current heading, lies along the
 *      center-line of a 2D image frame. If the frame is perfectly level (0 roll), then this will
 *      be the vertical line passing through the middle of the top and the bottom of the frame.
 *      With non-zero roll, this is the line perpendicular to the horizon passing through the center
 *      of the frame (the point [width/2, height/2]).
 *
 *  (2) The angle between the current heading and any point in 3D space can be estimated by
 *      the distance between the projection of that point onto the 2D image plane and the
 *      center-line of that image.
 *
 * These assumptions should in principle be correct if the camera is at a negligible radius
 *  from the center of rotation in the roll axis.
 */
class SimpleDangerZoneEncoder: public DangerZoneEncoder {

  public:

    SimpleDangerZoneEncoder();

    std::vector <DangerZone> identifyDangerZones(const ObstaclePositionFrame &obstacleFrame) const;

  private:

    double calculateDistanceFromCenterLine(Line centerLine, cv::Point2d p) const;
};


#endif //OBSTACLE_AVOIDANCE_SIMPLEDANGERZONEENCODER_H
