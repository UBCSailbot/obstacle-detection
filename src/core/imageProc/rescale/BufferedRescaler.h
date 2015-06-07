//
// Created by paul on 02/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_BUFFEREDRESCALER_H
#define OBSTACLE_AVOIDANCE_BUFFEREDRESCALER_H


#include <queue>
#include <imageProc/core/ImageHistogram.h>
#include "Rescaler.h"

class BufferedRescaler : public Rescaler {
public:
    static const int DEFAULT_BUFFER_SIZE = 100;

    BufferedRescaler(int bufferSize);

protected:
    int calculateBufferedPeakValue(int &peakValue);

    std::queue<int> _histogramPeakBuffer;
    int _bufferRunningSum;
    int _bufferCapacity;
};


#endif //OBSTACLE_AVOIDANCE_BUFFEREDRESCALER_H
