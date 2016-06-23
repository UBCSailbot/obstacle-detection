//
// Created by paul on 15/01/16.
//

#ifndef OBSTACLE_DETECTION_OBSTACLE_H
#define OBSTACLE_DETECTION_OBSTACLE_H

#include <vector>
#include <limits>
#include <algorithm>
#include <opencv2/core/core.hpp>
#include <geometry/Horizon.h>

/**
 * Describes an obstacle as a set of points on the coordinate plane of an image.
 */
class Obstacle {

  public:

    /**
     * Constructs an obstacle from the given set of points. A typical way to
     *  represent an obstacle is using a bounding box, but this class is not
     *  restricted to that type of representation for an obstacle.
     *
     * Also takes in a Horizon to determine the orientation of the obstacle.
     *  Since an obstacle exists in the context of the image frame in which
     *  it was detected, the horizon line of that image is a useful tool
     *  for situating the obstacle within the scene.
     *
     * TODO: How to break ties on getPortmost and getStarboardmost vertices?
     */
    Obstacle(std::vector <cv::Point2f> vertices, const Horizon &horizon);

    /**
     * Returns the vector of points that was passed in to construct this
     *  object.
     */
    const std::vector <cv::Point2f> getVertices() const;

    /**
     * Returns the vertex of the obstacle that is the furthest to the port
     *  side relative to the boat's current heading. (PORT == LEFT)
     */
    cv::Point2f getPortmostVertex()const;

    /**
     * Returns the vertex of the obstacle that is the furthest to the starboard
     *  side relative to the boat's current heading. (STARBOARD == RIGHT)
     */
    cv::Point2f getStarboardmostVertex()const;

    /**
     * Return the number of vertices used to represent this obstacle.
     */
    size_t numVertices() const;

  private:
    std::vector <cv::Point2f> _vertices;
    Horizon _horizon;

    /**
     * This is a custom comparator used to sort the vertices of this obstacle
     *  according to how far they are to the port side of the boat's current
     *  heading.
     */
    struct ObstaclePointComparator {
        ObstaclePointComparator(const Horizon &h) : _horizon(h) { }
        bool operator()(cv::Point2f p1, cv::Point2f p2);
        const Horizon &_horizon;
    };

};

#endif //OBSTACLE_DETECTION_OBSTACLE_H
