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
    ~DesktopDisplay();
    void displayFrame(Image8bit image);

};


#endif //OBSTACLE_AVOIDANCE_DESKTOPDISPLAY_H

