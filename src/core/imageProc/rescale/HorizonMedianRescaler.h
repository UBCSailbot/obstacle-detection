//
// Created by paul on 01/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_HORIZONMEDIALRESCALER_H
#define OBSTACLE_AVOIDANCE_HORIZONMEDIALRESCALER_H


#include <imageTypes/Image16bit.h>
#include <geometry/Horizon.h>
#include <imageTypes/Image8bit.h>
#include "imageProc/smoothing/AveragedBufferedSmoother.h"
#include "Rescaling.h"
#include "HorizonRescaler.h"
#include <imageProc/histogram/HorizonImageHistogram.h>


class HorizonMedianRescaler : public HorizonRescaler {

public:
    HorizonMedianRescaler(int bufferSize = AveragedBufferedSmoother::DEFAULT_BUFFER_SIZE);
    void scale16bitTo8bit(const Image16bit &src, const Horizon &horizon, Image8bit &dst);

protected:
    AveragedBufferedSmoother peakSmoother;

};


#endif //OBSTACLE_AVOIDANCE_HORIZONMEDIALRESCALER_H
