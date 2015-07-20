//
// Created by paul on 11/07/15.
//

#ifndef OBSTACLE_AVOIDANCE_DISPLAYUTILS_H
#define OBSTACLE_AVOIDANCE_DISPLAYUTILS_H

#include <geometry/Horizon.h>
#include <types/Image16bit.h>
#include <imageProc/rescale/Rescaler.h>
#include <imageProc/rescale/SimpleRescaler.h>
#include "display/Display.h"
#include "display/RoboPeakUSBDisplay.h"
#include "display/DesktopDisplay.h"

class DisplayUtils {

public:

    static Display* connectToDisplay();

    static void displayFrameWithHorizonLine(const Image8bit &frame,
                                                          double roll, double pitch, Display &d);

    static void rescaleAndDisplay(Image16bit img, Rescaler* r, Display &d);

    static size_t calculateScaleFactor(const cv::Mat &image, const size_t &displayWidth,
                                       const size_t &displayHeight);

};

#endif //OBSTACLE_AVOIDANCE_DISPLAYUTILS_H
