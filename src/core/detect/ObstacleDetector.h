//
// Created by paul on 04/08/15.
//

#ifndef OBSTACLE_AVOIDANCE_OBSTACLEDETECTOR_H
#define OBSTACLE_AVOIDANCE_OBSTACLEDETECTOR_H


#include <opencv2/core/core.hpp>

#include "geometry/Horizon.h"
#include "detect/ObstaclePositionFrame.h"

/**
 * Interface for all classes that detect obstacles in images.
 */
class ObstacleDetector {

  public:

    /**
     * Given a frame and a horizon line, detect the presence and/or position of any
     *  obstacles within the frame.
     */
    virtual const ObstaclePositionFrame detectObstacle(cv::Mat frame, Horizon h) = 0;

};


#endif //OBSTACLE_AVOIDANCE_OBSTACLEDETECTOR_H
