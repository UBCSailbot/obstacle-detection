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

int ImageHistogram::numBins() const {
    return (int) _histogramBins.size();
}

int ImageHistogram::getMode() {
    if (_tallestBinIndex == -1) {
        calculateModeBinIndex();
    }
    return _tallestBinIndex + _minPixelValue;
}


int ImageHistogram::getMedian() {
    if (_medianBinIndex == -1) {
        calculateMedianBinIndex();
    }
    return _medianBinIndex + _minPixelValue;
}


void ImageHistogram::calculateModeBinIndex() {
    int maxVal, maxIndex;
    maxVal = 0;
    maxIndex = 0;

    for (int i = 0; i < _histogramBins.size(); i++) {
        if (_histogramBins[i] > maxVal) {
            maxVal = _histogramBins[i];
            maxIndex = i;
        }
    }

    _tallestBinIndex = maxIndex;
}

void ImageHistogram::calculateMedianBinIndex() {
    int curDistanceFromMedianPixel = calculateMedianPixelIndex();

    for (int i = 0; i < _histogramBins.size(); i++) {
        curDistanceFromMedianPixel -= _histogramBins[i];
        if (curDistanceFromMedianPixel <= 0) {
            _medianBinIndex = i;
            break;
        }
    }
}

int ImageHistogram::calculateMedianPixelIndex() const {
    return (this->getNumPixels()) / 2;
}

int ImageHistogram::getNumPixelsWithValue(const int &pixelValue) const {
    int binIndex = pixelValue - _minPixelValue;
    if (binIndex < 0 || pixelValue > _maxPixelValue) {
        return 0;
    }
    return _histogramBins[binIndex];
}

void ImageHistogram::find8bitWindow(const int &medianValue, int &minValue, int &maxValue) const {
    int peakIndex = medianValue - _minPixelValue;

    // identify a legal min value
    minValue = (peakIndex - 127 < 0) ? _minPixelValue : medianValue - 127;

    // identify a legal max value
    maxValue = (peakIndex + 128 > _histogramBins.size()) ? _maxPixelValue : peakIndex + 128;
}