//
// Created by paul on 16/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_HISTOGRAMGENERATOR_H
#define OBSTACLE_AVOIDANCE_HISTOGRAMGENERATOR_H


#include <imageProc/histogram/ImageHistogram.h>
#include "geometry/Horizon.h"
#include "io/ObjectStream.h"

class HistogramGenerator {

public:

    virtual ImageHistogram generateHistogram(const cv::Mat &img) const = 0;

};


#endif //OBSTACLE_AVOIDANCE_HISTOGRAMGENERATOR_H
