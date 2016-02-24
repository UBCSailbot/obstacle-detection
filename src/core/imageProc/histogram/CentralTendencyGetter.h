//
// Created by paul on 16/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_CENTRALTENDENCY_H
#define OBSTACLE_AVOIDANCE_CENTRALTENDENCY_H


#include <imageProc/histogram/ImageHistogram.h>

class CentralTendencyGetter {

  public:
    CentralTendencyGetter(CentralTendencyGetter *decoratedGetter) : _decoratedGetter(decoratedGetter) { }

    virtual ~CentralTendencyGetter() {
        delete _decoratedGetter;
    }

    virtual int getCentralTendency(ImageHistogram histogram) = 0;

  protected:
    CentralTendencyGetter *_decoratedGetter;

};


#endif //OBSTACLE_AVOIDANCE_CENTRALTENDENCY_H
