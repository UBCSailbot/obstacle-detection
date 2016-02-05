//
// Created by paul on 15/01/16.
//

#include "Obstacle.h"

Obstacle::Obstacle(std::vector<cv::Point2f> vertices, const Horizon &horizon) :
        _vertices(vertices), _horizon(horizon)
{
    if (vertices.size() < 2)
    {
        throw std::invalid_argument("At least 2 vertices must be passed in to "
                                            "constructor for Obstacle.");
    }

    std::sort(_vertices.begin(), _vertices.end(), ObstaclePointComparator(_horizon));
}

const std::vector<cv::Point2f> Obstacle::getVertices() const
{
    return _vertices;
}

size_t Obstacle::numVertices() const
{
    return _vertices.size();
}

bool Obstacle::ObstaclePointComparator::operator()(cv::Point2f p1, cv::Point2f p2) {
    double p1DistanceAlongHorizon = _horizon.findPointClosestTo(p1);
    double p2DistanceAlongHorizon = _horizon.findPointClosestTo(p2);

    return p1DistanceAlongHorizon < p2DistanceAlongHorizon;

}

const cv::Point2f Obstacle::getPortmostVertex() {
    return _vertices.front();
}

const cv::Point2f Obstacle::getStarboardmostVertex() {
    return _vertices.back();
}
