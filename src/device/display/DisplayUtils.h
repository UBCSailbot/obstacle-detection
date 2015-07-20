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

    static Display* connectToDisplay() {
        Display* display = new RoboPeakUSBDisplay();
        if (!display->connected()) {
            delete display;
            display = new DesktopDisplay();
        }
        return display;
    }

    static void displayFrameWithHorizonLine(const Image8bit &frame, double roll, double pitch, Display &d) {
        Horizon h(roll, pitch);
        cv::Mat displayed(frame.rows, frame.cols, CV_16U);
        cv::cvtColor(frame, displayed, cv::COLOR_GRAY2BGR);
        cv::line(displayed, h.getStartPoint(), h.getEndPoint(), cv::Scalar(255,0,0), 1);
        d.displayColored(displayed);
    }

    static void rescaleAndDisplay(Image16bit img, Rescaler* r, Display &d) {
        Image8bit img8bit(img.rows, img.cols);

        r->scale16bitTo8bit(img, img8bit);

        d.display8bitGray(img8bit);

    }
};

#endif //OBSTACLE_AVOIDANCE_DISPLAYUTILS_H
