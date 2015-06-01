//
// Created by paul on 24/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_IMAGE_HISTOGRAM_H
#define OBSTACLE_AVOIDANCE_IMAGE_HISTOGRAM_H

#include <vector>
#include <opencv2/core/core.hpp>

/**
 * Stores information about the number of pixels of each value that occurs in
 *  a monochrome (grayscale) image.
 */
class ImageHistogram {

public:

    ImageHistogram(const cv::Mat &image);

    /**
     * Returns the number of pixels contained in this histogram.
     */
    int getNumPixels() const;

    /**
     * Returns the number of pixels contained in this histogram with the
     *  specified value. Handles all input gracefully - i.e. if the provided
     *  value falls outside the range of values contained in this histogram,
     *  this function (aptly) returns 0.
     */
    int getNumPixelsWithValue(const int &pixelValue) const;

    /**
     * Returns the most common pixel value contained in this histogram.
     *  If multiple pixel values are tied for the mode, this function
     *  returns the smallest such value.
     */
    int getMode();

    /**
     * Returns the median pixel value in this histogram. Note that since pixel
     *  values must necessarily be (positive) integers, this function does not
     *  give the true arithmetical median of the set of numbers stored in this
     *  histogram, but instead returns the floor() of the true median. (Thus a
     *  median of 7.5 would be floored down to 7).
     */
    int getMedian();

    /**
     * Returns the smallest pixel value contained in this histogram.
     */
    int getMinPixelValue() const;

    /**
     * Returns the largest pixel value contained in this histogram.
     */
    int getMaxPixelValue() const;

    /**
     * Returns the number of bins in this histogram (and hence the number of
     *  discrete pixel values contained in this histogram).
     */
    int numBins() const;

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
    void find8bitWindow(const int &medianValue, int &minValue, int &maxValue) const;

protected:
    /**
     * Protected default constructor for subclasses, so that superclass object is not
     *  needlessly populated.
     */
    ImageHistogram();
    std::vector<int> _histogramBins;
    int _minPixelValue;
    int _maxPixelValue;
    int _numPixels = 0;

private:
    int _tallestBinIndex = -1;
    int _medianBinIndex = -1;

    void populateHistogram(const cv::Mat &image);

    void calculateModeBinIndex();
    void calculateMedianBinIndex();
    int calculateMedianPixelIndex() const;

};

#endif //OBSTACLE_AVOIDANCE_IMAGE_HISTOGRAM_H
