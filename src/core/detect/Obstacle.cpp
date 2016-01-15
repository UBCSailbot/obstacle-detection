//
// Created by paul on 15/01/16.
//

#include <geometry/CommonOperations.h>
#include "Obstacle.h"

Obstacle::Obstacle(const std::vector<cv::Point2f> vertices) :
        _vertices(vertices)
{
    _portmostSet = false;
    _starboardmostSet = false;

    if (vertices.size() < 2)
    {
        throw std::invalid_argument("At least 2 vertices must be passed in to "
                                            "constructor for Obstacle.");
    }
}

const std::vector<cv::Point2f> Obstacle::getVertices() const
{
    return _vertices;
}

const cv::Point2f Obstacle::getPortmostVertex(Horizon frameOfReference)
{
    if (_portmostSet)
    {
        return _portmostVertex;
    }

    double horizonX = frameOfReference.getEndPoint().x - frameOfReference.getStartPoint().x;
    double horizonY = frameOfReference.getEndPoint().y - frameOfReference.getStartPoint().y;

    double portmostDistance = std::numeric_limits<double>::max();
    cv::Point2f portmostVertex = _vertices[0];

    for (cv::Point2f vertex : _vertices)
    {
        double portDistance = projectAontoB(vertex.x, vertex.y, horizonX, horizonY);

        if (portDistance < portmostDistance)
        {
            portmostVertex = vertex;
            portmostDistance = portDistance;
        }
    }

    _portmostSet = true;

    return portmostVertex;
}

const cv::Point2f Obstacle::getStarboardmostVertex(Horizon frameOfReference)
{
    if (_starboardmostSet)
    {
        return _starboardmostVertex;
    }

    double horizonX = frameOfReference.getEndPoint().x - frameOfReference.getStartPoint().x;
    double horizonY = frameOfReference.getEndPoint().y - frameOfReference.getStartPoint().y;

    double starboardmostDistance = 0;
    cv::Point2f starboardmostVertex = _vertices[0];

    for (cv::Point2f vertex : _vertices)
    {
        double starboardDistance = projectAontoB(vertex.x, vertex.y, horizonX, horizonY);

        if (starboardDistance > starboardmostDistance)
        {
            starboardmostVertex = vertex;
            starboardmostDistance = starboardDistance;
        }
    }

    _starboardmostSet = true;

    return starboardmostVertex;
}

size_t Obstacle::numVertices() const
{
    return _vertices.size();
}