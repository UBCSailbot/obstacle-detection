//
// Created by paul on 02/06/15.
//

#include "ValueSmoother.h"

int ValueSmoother::calculateSmoothedValue(int currentValue) {
    _histogramPeakBuffer.push(currentValue);
    _bufferRunningSum += currentValue;

    if (_histogramPeakBuffer.size() > _bufferCapacity) {
        _bufferRunningSum -= _histogramPeakBuffer.front();
        _histogramPeakBuffer.pop();
    }

    return _bufferRunningSum / (int) _histogramPeakBuffer.size();

}

ValueSmoother::ValueSmoother(int bufferSize) : _bufferCapacity(bufferSize) {


}