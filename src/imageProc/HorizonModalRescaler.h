//
// Created by paul on 23/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_HORIZONMODALRESCALER_H
#define OBSTACLE_AVOIDANCE_HORIZONMODALRESCALER_H


#include <queue>
#include "../imageTypes/Image16bit.h"
#include "../features/Horizon.h"
#include "../imageTypes/Image8bit.h"
#include "core/ImageHistogram.h"
#include "core/HorizonImageHistogram.h"

class HorizonModalRescaler {

public:
    HorizonModalRescaler(int bufferSize = 100);
    void scale16bitTo8bit(const Image16bit &src, const Horizon &horizon, Image8bit &dst);

private:
    int calculateBufferedPeakValue(ImageHistogram &histogram);
    void applyRescaling(const Image16bit &src, Image8bit &dst, const int &newMinPixelValue) const;

    std::queue<int> _histogramPeakBuffer;
    int _bufferRunningSum;
    int _bufferCapacity;
};


#endif //OBSTACLE_AVOIDANCE_HORIZONMODALRESCALER_H
