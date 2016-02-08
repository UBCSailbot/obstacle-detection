//
// Created by denis on 06/02/16.
//

#include <dlib/opencv/cv_image.h>
#include "DLibProcessor.h"


DLibProcessor::DLibProcessor(std::vector<dlib::object_detector<image_scanner_type> > detectors) {
    this->detectors = detectors;

}

DLibProcessor::~DLibProcessor(){

}

std::vector<dlib::rectangle> DLibProcessor::getBoxes(Image8bit image) {

    dlib::cv_image<dlib::hsi_pixel> img(image);

    std::vector<dlib::rectangle> dets =   evaluate_detectors(detectors, img);

    return std::vector<dlib::rectangle>();

}
