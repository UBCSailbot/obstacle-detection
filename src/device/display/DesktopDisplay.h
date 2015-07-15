//
// Created by paul on 12/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_DESKTOPDISPLAY_H
#define OBSTACLE_AVOIDANCE_DESKTOPDISPLAY_H

#include "Display.h"

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

    static const size_t MIN_WIDTH = 640;
    static const size_t MIN_HEIGHT = 480;

private:
    void calculateScaleFactors(const cv::Mat &image, size_t &xScaleFactor, size_t &yScaleFactor) const;
};


#endif //OBSTACLE_AVOIDANCE_DESKTOPDISPLAY_H

