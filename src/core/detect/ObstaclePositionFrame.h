//
// Created by paul on 08/08/15.
//

#ifndef OBSTACLE_AVOIDANCE_OBSTACLEFRAME_H
#define OBSTACLE_AVOIDANCE_OBSTACLEFRAME_H

#include <vector>
#include <utility>
#include <opencv2/core/core.hpp>
#include <geometry/Horizon.h>

/**
 * When an obstacle is detected in a frame, the most useful pieces of information
 *  are the locations of its edges within the frame. This class acts as a container
 *  for this information, along with the supporting information needed to infer the
 *  triangular region within which the obstacle might be present in the real world,
 *  relative to the boat's current heading.
 */
class ObstaclePositionFrame {

public:
    ObstaclePositionFrame(const cv::Mat &frame, int xFOV, int yFOV,
                          const std::vector<std::pair<double, double>> &obstacleEdges) :
            _rows(frame.rows), _cols(frame.cols), _xFOV(xFOV), _yFOV(yFOV),
            _obstacleEdges(obstacleEdges)
    {    }

    const bool containsObstacle() {
        return !_obstacleEdges.empty();
    }

    const std::vector<std::pair<double, double>> getObstacleEdges() const {
        return _obstacleEdges;
    }

    const int getRows() const {
        return _rows;
    }

    const int getCols() const {
        return _cols;
    }

    const double getXFOV() const {
        return _xFOV;
    }

    const double getYFOV() const {
        return _yFOV;
    }

private:
    //with reference to the horizon
    std::vector<std::pair<double, double>> _obstacleEdges;
    int _rows;
    int _cols;
    double _xFOV;
    double _yFOV;

};


#endif //OBSTACLE_AVOIDANCE_OBSTACLEFRAME_H
