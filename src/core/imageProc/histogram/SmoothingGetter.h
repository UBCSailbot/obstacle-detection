//
// Created by paul on 16/06/15.
//

#include "CentralTendencyGetter.h"
#include <imageProc/smoothing/BufferedSmoother.h>

#ifndef OBSTACLE_AVOIDANCE_SMOOTHINGGETTER_H
#define OBSTACLE_AVOIDANCE_SMOOTHINGGETTER_H

class SmoothingGetter : public CentralTendencyGetter {

public:
    SmoothingGetter(CentralTendencyGetter *decoratedGetter, BufferedSmoother *bufferedSmoother)
            : CentralTendencyGetter(decoratedGetter), _bufferedSmoother(bufferedSmoother) {}

    virtual ~SmoothingGetter() {
        delete _bufferedSmoother;
    }

    int getCentralTendency(ImageHistogram histogram) {
        int centralValue = _decoratedGetter->getCentralTendency(histogram);
        return _bufferedSmoother->calculateSmoothedValue(centralValue);
    }

private:
    BufferedSmoother* _bufferedSmoother;
};

#endif //OBSTACLE_AVOIDANCE_SMOOTHINGGETTER_H
