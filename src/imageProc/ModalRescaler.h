//
// Created by paul on 12/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_MODALRESCALER_H
#define OBSTACLE_AVOIDANCE_MODALRESCALER_H

#include "Rescaler.h"

class ModalRescaler : public Rescaler {
public:

    ModalRescaler();
    ~ModalRescaler();

    void scale16bitTo8bit(Image16bit src, Image8bit dst);
};


#endif //OBSTACLE_AVOIDANCE_MODALRESCALER_H
