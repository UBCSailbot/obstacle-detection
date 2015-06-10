//
// Created by paul on 09/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_HORIZONRESCALER_H
#define OBSTACLE_AVOIDANCE_HORIZONRESCALER_H


#include "imageTypes/Image16bit.h"
#include "geometry/Horizon.h"
#include "imageTypes/Image8bit.h"

class HorizonRescaler {

public:
    virtual void scale16bitTo8bit(const Image16bit &src, const Horizon &h, Image8bit &dst) = 0;

};

#endif //OBSTACLE_AVOIDANCE_HORIZONRESCALER_H
