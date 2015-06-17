//
// Created by paul on 16/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_HORIZONHISTOGRAMGENERATOR_H
#define OBSTACLE_AVOIDANCE_HORIZONHISTOGRAMGENERATOR_H


#include <imageProc/histogram/HorizonImageHistogram.h>
#include "HistogramGenerator.h"

class HorizonHistogramGenerator : public HistogramGenerator {

public:
    HorizonHistogramGenerator(ObjectStream<Horizon>* horizonStream) :
            _horizonStream(horizonStream)
    { }

    virtual ~HorizonHistogramGenerator() {
        delete _horizonStream;
    }

    ImageHistogram generateHistogram(const cv::Mat &image) const {
        return HorizonImageHistogram(image, _horizonStream->next());
    }


private:
    ObjectStream<Horizon>* _horizonStream;

};


#endif //OBSTACLE_AVOIDANCE_HORIZONHISTOGRAMGENERATOR_H
