//
// Created by paul on 02/06/15.
//

#include "WeightedAverageBufferedSmoother.h"

AveragedBufferedSmoother::AveragedBufferedSmoother(int bufferSize) : _bufferCapacity(bufferSize) {

}

AveragedBufferedSmoother::AveragedBufferedSmoother() {
    _bufferCapacity = DEFAULT_BUFFER_SIZE;
}

int AveragedBufferedSmoother::calculateSmoothedValue(int currentValue, float weight) {
    long weightedCurrentValue = (long) (currentValue * weight);
    _valueBuffer.push(weightedCurrentValue);
    _bufferRunningSum += weightedCurrentValue;

    _weightBuffer.push(weight);
    _weightsRunningSum += weight;

    if (_valueBuffer.size() > _bufferCapacity) {
        _bufferRunningSum -= _valueBuffer.front();
        _valueBuffer.pop();

        _weightsRunningSum -= _weightBuffer.front();
        _weightBuffer.pop();
    }

    if (_weightsRunningSum == 0) {
        return 0;
    } else {
        return (int) (_bufferRunningSum / _weightsRunningSum);
    }

}

