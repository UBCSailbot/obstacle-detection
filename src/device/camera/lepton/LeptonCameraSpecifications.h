//
// Created by Derek Lun on 5/23/2015.
//

#ifndef OBSTACLE_AVOIDANCE_LEPTONCAMERADIMENSIONS_H
#define OBSTACLE_AVOIDANCE_LEPTONCAMERADIMENSIONS_H

#include <camera/ICameraSpecifications.h>

#define VIEWPORT_HEIGHT_PIX 60
#define VIEWPORT_WIDTH_PIX 80
#define VIEWPORT_FOV_DEGREES_VERTICAL 37
#define VIEWPORT_FOV_DEGREES_HORIZONTAL 51

/**
 *
 */
static const ICameraSpecifications LeptonCameraSpecifications = {
        60,  // pixelHeight
        80,  // pixelWidth
        37,  // FOVDegreesVertical
        51   // FOVDegreesHorizontal
};

#endif //OBSTACLE_AVOIDANCE_LEPTONCAMERADIMENSIONS_H
