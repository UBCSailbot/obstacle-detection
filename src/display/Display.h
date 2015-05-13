//
// Created by paul on 12/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_DISPLAY_H
#define OBSTACLE_AVOIDANCE_DISPLAY_H

#include <opencv2/core/core.hpp>

/**
 * Interface for displays on which to show visual output.
 */
class Display {

public:
    virtual ~Display() {}
    virtual void displayFrame(cv::Mat image) = 0;
};

#endif //OBSTACLE_AVOIDANCE_DISPLAY_H
