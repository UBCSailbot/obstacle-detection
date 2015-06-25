//
// Created by paul on 16/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_MEDIANGETTER_H
#define OBSTACLE_AVOIDANCE_MEDIANGETTER_H

#include "CentralTendencyGetter.h"

class MedianGetter : public CentralTendencyGetter{

public:

    MedianGetter() : CentralTendencyGetter(nullptr) { }

    int getCentralTendency(ImageHistogram histogram) {
        return histogram.getMedian();
    }

};


#endif //OBSTACLE_AVOIDANCE_MEDIANGETTER_H
