//
// Created by paul on 24/05/15.
//

#include "ImageHistogram.h"

int ImageHistogram::getMinPixelValue() const {
    return _minPixelValue;
}

int ImageHistogram::getMaxPixelValue() const {
    return _maxPixelValue;
}

int ImageHistogram::size() const {
    return 0;
}

int ImageHistogram::getMode() {
    if (_tallestBinIndex == -1) {
        calculateMode();
    }

    return _tallestBinIndex + _minPixelValue;

}

void ImageHistogram::calculateMode() {
    int maxVal, maxIndex;
    maxVal = 0; maxIndex = 0;

    for (int i=0; i < _histogramBins.size(); i++) {
        if (_histogramBins[i] > maxVal) {
            maxVal = _histogramBins[i];
            maxIndex = i;
        }
    }

    _tallestBinIndex = maxIndex;

}

int ImageHistogram::getNumPixelsWithValue(const int &pixelValue) const {
    return _histogramBins[pixelValue];
}

void ImageHistogram::find8bitWindow(const int &medianValue, int &minValue, int &maxValue) const {
    int peakIndex = medianValue - _minPixelValue;

    // identify a legal min value
    minValue = (peakIndex - 127 < 0) ? _minPixelValue : medianValue - 127;

    // identify a legal max value
    maxValue = (peakIndex + 128 > _histogramBins.size()) ? _maxPixelValue : peakIndex + 128;
}
