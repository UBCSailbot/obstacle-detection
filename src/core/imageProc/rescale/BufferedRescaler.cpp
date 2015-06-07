//
// Created by paul on 02/06/15.
//

#include "BufferedRescaler.h"

int BufferedRescaler::calculateBufferedPeakValue(int &peakValue) {
    _histogramPeakBuffer.push(peakValue);
    _bufferRunningSum += peakValue;

    if (_histogramPeakBuffer.size() > _bufferCapacity) {
        peakValue = _bufferRunningSum / _bufferCapacity;
        _bufferRunningSum -= _histogramPeakBuffer.front();
        _histogramPeakBuffer.pop();
    }

    return peakValue;

}

BufferedRescaler::BufferedRescaler(int bufferSize) : _bufferCapacity(bufferSize) {


}
