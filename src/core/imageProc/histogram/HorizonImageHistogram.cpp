//
// Created by paul on 23/05/15.
//

#include "HorizonImageHistogram.h"

HorizonImageHistogram::HorizonImageHistogram(const cv::Mat &image, const Horizon &horizon)
{
    // TODO: find more efficient implementation for sparse histograms
    double min, max;
    minMaxLoc(image, &min, &max);
    int histogramSize = (int) (max - min + 1);

    _histogramBins = std::vector<int>(histogramSize, 0);
    _minPixelValue = (int) min;
    _maxPixelValue = (int) max;

    populateHistogram(image, horizon);
}


void HorizonImageHistogram::populateHistogram(const cv::Mat &image, const Horizon &horizon) {
    for (int row=0; row < image.rows; row++) {
        for (int col=0; col < image.cols; col++) {
            if (!horizon.isPointAbove(col, row)) {
                int i = image.at<uint16_t>(row, col) - _minPixelValue;
                _histogramBins[i]++;
                _numPixels++;
            }
        }
    }
}
