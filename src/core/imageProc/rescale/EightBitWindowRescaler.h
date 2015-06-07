//
// Created by paul on 25/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_EIGHTBITWINDOWRESCALER_H
#define OBSTACLE_AVOIDANCE_EIGHTBITWINDOWRESCALER_H


#include "imageTypes/Image16bit.h"
#include "imageTypes/Image8bit.h"
#include "Rescaler.h"

class EightBitWindowRescaler : public Rescaler {

protected:
    void applyRescaling(const Image16bit &src, Image8bit &dst, const int &newMinPixelValue) const;
};


#endif //OBSTACLE_AVOIDANCE_EIGHTBITWINDOWRESCALER_H
