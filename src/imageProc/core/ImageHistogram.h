//
// Created by paul on 24/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_IMAGE_HISTOGRAM_H
#define OBSTACLE_AVOIDANCE_IMAGE_HISTOGRAM_H

#include <vector>

class ImageHistogram {
public:

    virtual int getNumPixelsWithValue(const int &pixelValue) const;
    virtual int getMode();
    virtual int getMinPixelValue() const;
    virtual int getMaxPixelValue() const;
    virtual int size() const;

    /**
     * Finds a window of pixel values represented within this histogram that is at most
     *  8 bits wide, distributed as evenly as possible around the given median.
     *
     * PRE: medianValue is a value that corresponds to one of the bins of this histogram.
     *  If medianValue is a pixel value that falls outside of this histogram, this function
     *  behaves as if medianValue were the minimum or maximum value in the histogram,
     *  respectively, depending on whether medianValue is greater than the histogram max
     *  or less than the histogram min.
     *
     * POST: minValue and maxValue are set such that maxValue - minValue <= 255 .
     *  maxValue and minValue are guaranteed to be set to values that fall within this
     *  histogram. This means that if the entire range of this histogram is narrower than
     *  8 bits, then minValue and maxValue are simply set to the histogram min and max,
     *  respectively.
     *  Furthermore, minValue and maxValue are selected to lie as evenly as possible on
     *  either side of medianValue. In the simplest case, this means that minValue =
     *  medianValue - 127 , and maxValue = medianValue + 128. If either of these updated
     *  values falls outside this histogram, then they are clipped to the histogram min
     *  or max, respectively.
     */
    virtual void find8bitWindow(const int &medianValue, int &minValue, int &maxValue) const;

protected:
    std::vector<int> _histogramBins;
    int _minPixelValue;
    int _maxPixelValue;
    int _tallestBinIndex;

private:
    void calculateMode();

};

#endif //OBSTACLE_AVOIDANCE_IMAGE_HISTOGRAM_H
