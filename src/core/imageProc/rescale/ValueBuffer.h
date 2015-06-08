//
// Created by paul on 02/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_BUFFEREDRESCALER_H
#define OBSTACLE_AVOIDANCE_BUFFEREDRESCALER_H


#include <queue>

class ValueBuffer {
public:
    static const int DEFAULT_BUFFER_SIZE = 100;

    ValueBuffer(int bufferSize);
    int calculateBufferedValue(int &peakValue);

protected:
    std::queue<int> _histogramPeakBuffer;
    int _bufferRunningSum;
    int _bufferCapacity;
};


#endif //OBSTACLE_AVOIDANCE_BUFFEREDRESCALER_H
