//
// Created by paul on 23/05/15.
//

#include "HorizonModalRescaler.h"


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

void HorizonModalRescaler::applyRescaling(const Image16bit &src, Image8bit &dst, const int &newMinPixelValue) const
{
    // TODO: check that the output image already has memory allocated to it.
    for (int row = 0; row < src.rows; row++) {
        for (int col = 0; col < src.cols; col++) {
            int scaledValue = src.at<uint16_t>(row, col) - newMinPixelValue;
            if (scaledValue > 255)
                scaledValue = 255;
            else if (scaledValue < 0)
                scaledValue = 0;
            dst.at<uint8_t>(row, col) = (uint8_t) scaledValue;
        }
    }

}
