//
// Created by paul on 12/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_RESCALER_H
#define OBSTACLE_AVOIDANCE_RESCALER_H

#include "imageTypes/Image16bit.h"
#include "imageTypes/Image8bit.h"

class Rescaler {

public:
    virtual void scale16bitTo8bit(const Image16bit &src, Image8bit &dst) = 0;

};

#endif //OBSTACLE_AVOIDANCE_RESCALER_H
