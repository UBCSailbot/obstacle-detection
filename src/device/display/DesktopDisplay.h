//
// Created by paul on 12/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_DESKTOPDISPLAY_H
#define OBSTACLE_AVOIDANCE_DESKTOPDISPLAY_H

#include <opencv2/highgui/highgui.hpp>

#include "display/Display.h"
#include "types/Image8bit.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "display/DisplayUtils.h"


/**
 * A simple implementation of the Display interface that simply displays an image on the native
 *  monitor.
 */
class DesktopDisplay: public Display {
public:
    DesktopDisplay();
    virtual ~DesktopDisplay();
    void display8bitGray(const Image8bit &image);
    void displayColored(const cv::Mat &image);

    static const size_t MIN_WIDTH;
    static const size_t MIN_HEIGHT;

};


#endif //OBSTACLE_AVOIDANCE_DESKTOPDISPLAY_H

