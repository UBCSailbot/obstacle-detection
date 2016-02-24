//
// Created by paul on 01/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_HORIZONMEDIALRESCALER_H
#define OBSTACLE_AVOIDANCE_HORIZONMEDIALRESCALER_H


#include "types/Image16bit.h"
#include "geometry/Horizon.h"
#include "types/Image8bit.h"
#include "imageProc/smoothing/WeightedAverageBufferedSmoother.h"
#include "imageProc/rescale/Rescaling.h"
#include "imageProc/histogram/CentralTendencyGetter.h"
#include "imageProc/histogram/HistogramGenerator.h"
#include "imageProc/histogram/HorizonImageHistogram.h"


class ClippingRescaler: public Rescaler {

  public:
    ClippingRescaler(HistogramGenerator *histogramGenerator,
                     CentralTendencyGetter *centralTendencyGetter);
    virtual ~ClippingRescaler();

    virtual void scale16bitTo8bit(const Image16bit &src, Image8bit &dst);

  private:
    HistogramGenerator *_histogramGenerator;
    CentralTendencyGetter *_centralTendencyGetter;

};


#endif //OBSTACLE_AVOIDANCE_HORIZONMEDIALRESCALER_H
