//
// Created by paul on 16/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_MODEGETTER_H
#define OBSTACLE_AVOIDANCE_MODEGETTER_H


#include "CentralTendencyGetter.h"

class ModeGetter: public CentralTendencyGetter {

  public:
    ModeGetter() : CentralTendencyGetter(nullptr) { }

    int getCentralTendency(ImageHistogram histogram) {
        return histogram.getMode();
    }

};


#endif //OBSTACLE_AVOIDANCE_MODEGETTER_H
