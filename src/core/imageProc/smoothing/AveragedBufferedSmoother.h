//
// Created by paul on 02/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_VALUESMOOTHER_H
#define OBSTACLE_AVOIDANCE_VALUESMOOTHER_H


#include <queue>

#include "BufferedSmoother.h"

/**
 * Keeps a running average of the past _BUFFER_SIZE values seen,
 *  where _BUFFER_SIZE is the size of this object's recent memory.
 */
class AveragedBufferedSmoother : public BufferedSmoother {
public:
    static const int DEFAULT_BUFFER_SIZE = 100;

    AveragedBufferedSmoother();
    AveragedBufferedSmoother(int bufferSize);
    virtual int calculateSmoothedValue(int currentValue);

protected:
    std::queue<int> _valueBuffer;
    int _bufferRunningSum = 0;
    int _bufferCapacity;
};


#endif //OBSTACLE_AVOIDANCE_BUFFEREDRESCALER_H
