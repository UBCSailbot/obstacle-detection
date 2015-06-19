//
// Created by paul on 23/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_HORIZONRESCALER_H
#define OBSTACLE_AVOIDANCE_HORIZONRESCALER_H

#include "../horizon/Horizon.h"

class HorizonRescaler {

public:
    virtual ~HorizonRescaler();
    virtual void scale16bitTo8bit(const Image16bit &src, const Horizon &horizon, Image8bit &dst) = 0;

};


#endif //OBSTACLE_AVOIDANCE_HORIZONRESCALER_H
