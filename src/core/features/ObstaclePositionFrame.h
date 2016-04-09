//
// Created by paul on 08/08/15.
//

#ifndef OBSTACLE_AVOIDANCE_OBSTACLEFRAME_H
#define OBSTACLE_AVOIDANCE_OBSTACLEFRAME_H

#include <vector>
#include <utility>
#include <opencv2/core/core.hpp>
#include <geometry/Horizon.h>
#include <features/HorizonImage.h>
#include "detect/Obstacle.h"

/**
 * When an obstacle is detected in a frame, the most useful pieces of information
 *  are the locations of its edges within the frame. This class acts as a container
 *  for this information, along with the supporting information needed to infer the
 *  triangular region within which the obstacle might be present in the real world,
 *  relative to the boat's current heading.
 */
class ObstaclePositionFrame: public HorizonImage {

  public:
    ObstaclePositionFrame(const cv::Mat &frame, const Horizon &horizon,
                          const CameraSpecifications &cameraSpec,
                          const std::vector <Obstacle> &obstacles) :
        HorizonImage(frame, horizon),
        _obstacles(obstacles),
        _cameraSpec(cameraSpec) { }

    const bool containsObstacle() {
        return !_obstacles.empty();
    }

    const std::vector <Obstacle> getObstacles() const {
        return _obstacles;
    }

    const int getFrameHeight() const {
        return _image.rows;
    }

    const int getFrameWidth() const {
        return _image.cols;
    }

    const double getXFOV() const {
        return _cameraSpec.FOVDegreesHorizontal;
    }

    const double getYFOV() const {
        return _cameraSpec.FOVDegreesVertical;
    }

  private:
    //with reference to the horizon
    std::vector <Obstacle> _obstacles;
    CameraSpecifications _cameraSpec;

};


#endif //OBSTACLE_AVOIDANCE_OBSTACLEFRAME_H
