//
// Created by paul on 16/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_SIMPLEHISTOGRAMGENERATOR_H
#define OBSTACLE_AVOIDANCE_SIMPLEHISTOGRAMGENERATOR_H


#include "HistogramGenerator.h"

class SimpleHistogramGenerator : public HistogramGenerator {

public:
    ImageHistogram generateHistogram(const cv::Mat &image) const {
        return ImageHistogram(image);
    }


};


#endif //OBSTACLE_AVOIDANCE_SIMPLEHISTOGRAMGENERATOR_H
