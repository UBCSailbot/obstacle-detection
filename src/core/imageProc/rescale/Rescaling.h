//
// Created by paul on 25/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_EIGHTBITWINDOWRESCALER_H
#define OBSTACLE_AVOIDANCE_EIGHTBITWINDOWRESCALER_H

#include <types/Image16bit.h>
#include <types/Image8bit.h>
#include "Rescaler.h"

typedef enum {
    SIMPLE = 1,
    MODAL,
    MEDIAN
} RescalingType;

class Rescaling {

  public:
    static void clipTo8bitsCompress2to1(const Image16bit &src, Image8bit &dst, const int &newMidPixelValue);

    static void clipTo8bitsNoCompression(const Image16bit &src, Image8bit &dst, const int &newMidPixelValue);
};


#endif //OBSTACLE_AVOIDANCE_EIGHTBITWINDOWRESCALER_H
