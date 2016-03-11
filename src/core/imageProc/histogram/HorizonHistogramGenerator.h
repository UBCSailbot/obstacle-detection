//
// Created by paul on 16/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_HORIZONHISTOGRAMGENERATOR_H
#define OBSTACLE_AVOIDANCE_HORIZONHISTOGRAMGENERATOR_H


#include <imageProc/histogram/HorizonImageHistogram.h>
#include "HistogramGenerator.h"

class HorizonHistogramGenerator: public HistogramGenerator {

  public:
    HorizonHistogramGenerator(ObjectStream <Orientation> *orientationStream) :
        _orientationStream(orientationStream),
        _horizonFactory(HorizonFactory(LeptonCameraSpecifications)) {

    }

    virtual ~HorizonHistogramGenerator() {
        delete _orientationStream;
    }

    ImageHistogram generateHistogram(const cv::Mat &image) const {
        return HorizonImageHistogram(image,
                                     _horizonFactory.makeHorizon(_orientationStream->next()));
    }


  private:
    ObjectStream <Orientation> *_orientationStream;
    HorizonFactory _horizonFactory;

};


#endif //OBSTACLE_AVOIDANCE_HORIZONHISTOGRAMGENERATOR_H
