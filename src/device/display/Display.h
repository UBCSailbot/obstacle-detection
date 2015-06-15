//
// Created by paul on 12/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_DISPLAY_H
#define OBSTACLE_AVOIDANCE_DISPLAY_H

#include <opencv2/core/core.hpp>
#include "imageTypes/Image8bit.h"

/**
 * Interface for displays on which to show visual output.
 */
class Display {

public:
    virtual ~Display() {}
    virtual void displayFrame(Image8bit image) = 0;
    virtual void displayColorFrame(cv::Mat image) = 0;
};

#endif //OBSTACLE_AVOIDANCE_DISPLAY_H
