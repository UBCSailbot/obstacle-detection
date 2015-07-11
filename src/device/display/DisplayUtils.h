//
// Created by paul on 11/07/15.
//

#ifndef OBSTACLE_AVOIDANCE_DISPLAYUTILS_H
#define OBSTACLE_AVOIDANCE_DISPLAYUTILS_H

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
};

#endif //OBSTACLE_AVOIDANCE_DISPLAYUTILS_H
