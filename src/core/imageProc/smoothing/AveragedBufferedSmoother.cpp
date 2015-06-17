//
// Created by paul on 02/06/15.
//

#include "AveragedBufferedSmoother.h"

AveragedBufferedSmoother::AveragedBufferedSmoother(int bufferSize) : _bufferCapacity(bufferSize) {

}

AveragedBufferedSmoother::AveragedBufferedSmoother() {
    _bufferCapacity = DEFAULT_BUFFER_SIZE;
}

int AveragedBufferedSmoother::calculateSmoothedValue(int currentValue) {
    _valueBuffer.push(currentValue);
    _bufferRunningSum += currentValue;

    if (_valueBuffer.size() > _bufferCapacity) {
        _bufferRunningSum -= _valueBuffer.front();
        _valueBuffer.pop();
    }

    return _bufferRunningSum / (int) _valueBuffer.size();

}

