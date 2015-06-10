//
// Created by paul on 02/06/15.
//

#include "AveragedBufferedSmoother.h"

int AveragedBufferedSmoother::calculateSmoothedValue(int currentValue) {
    _valueBuffer.push(currentValue);
    _bufferRunningSum += currentValue;

    if (_valueBuffer.size() > _bufferCapacity) {
        _bufferRunningSum -= _valueBuffer.front();
        _valueBuffer.pop();
    }

    return _bufferRunningSum / (int) _valueBuffer.size();

}

AveragedBufferedSmoother::AveragedBufferedSmoother(int bufferSize) : _bufferCapacity(bufferSize) {


}