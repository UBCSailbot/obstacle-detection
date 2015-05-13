//
// Created by paul on 12/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_SIMPLERESCALER_H
#define OBSTACLE_AVOIDANCE_SIMPLERESCALER_H

#include "Rescaler.h"

class SimpleRescaler : public Rescaler {

public:
    SimpleRescaler();
    ~SimpleRescaler();
    void scale16bitTo8bit(Image16bit src, Image8bit dst);

};


#endif //OBSTACLE_AVOIDANCE_SIMPLERESCALER_H