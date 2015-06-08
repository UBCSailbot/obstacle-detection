//
// Created by paul on 02/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_VALUESMOOTHER_H
#define OBSTACLE_AVOIDANCE_VALUESMOOTHER_H


#include <queue>

class ValueSmoother {
public:
    static const int DEFAULT_BUFFER_SIZE = 100;

    ValueSmoother(int bufferSize);
    int calculateSmoothedValue(int &peakValue);

protected:
    std::queue<int> _histogramPeakBuffer;
    int _bufferRunningSum = 0;
    int _bufferCapacity;
};


#endif //OBSTACLE_AVOIDANCE_BUFFEREDRESCALER_H
