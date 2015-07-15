//
// Created by paul on 12/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_DISPLAY_H
#define OBSTACLE_AVOIDANCE_DISPLAY_H

#include <opencv2/core/core.hpp>
#include "types/Image8bit.h"

/**
 * Interface for displays on which to show visual output.
 */
class Display {

public:
    virtual ~Display() {}
    virtual void display8bitGray(const Image8bit &image) = 0;
    virtual void displayColored(const cv::Mat &image) = 0;

    bool connected() const {
        return _connected;
    }

protected:
    bool _connected;
};



#endif //OBSTACLE_AVOIDANCE_DISPLAY_H
