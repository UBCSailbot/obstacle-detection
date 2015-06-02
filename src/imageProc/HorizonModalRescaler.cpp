//
// Created by paul on 23/05/15.
//

#include "HorizonModalRescaler.h"
#include "EightBitWindowRescaler.h"


HorizonModalRescaler::HorizonModalRescaler(int bufferSize) : _bufferCapacity(bufferSize) {

}

void HorizonModalRescaler::scale16bitTo8bit(const Image16bit &src, const Horizon &horizon, Image8bit &dst) {
    HorizonImageHistogram histogram(src, horizon);
    int peakValue = calculateBufferedPeakValue(histogram);

    int newMinPixelValue, newMaxPixelValue;
    histogram.find8bitWindow(peakValue, newMinPixelValue, newMaxPixelValue);

    applyRescaling(src, dst, newMinPixelValue);
}

int HorizonModalRescaler::calculateBufferedPeakValue(ImageHistogram &histogram) {
    int peakValue = histogram.getMode();
    _histogramPeakBuffer.push(peakValue);
    _bufferRunningSum += peakValue;

    if (_histogramPeakBuffer.size() > _bufferCapacity) {
        peakValue = _bufferRunningSum / _bufferCapacity;
        _bufferRunningSum -= _histogramPeakBuffer.front();
        _histogramPeakBuffer.pop();
    }

    return peakValue;
}

