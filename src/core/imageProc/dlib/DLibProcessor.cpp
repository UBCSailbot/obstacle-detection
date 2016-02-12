//
// Created by denis on 06/02/16.
//

#include <dlib/opencv/cv_image.h>
#include "DLibProcessor.h"


DLibProcessor::DLibProcessor(std::vector<dlib::object_detector<image_scanner_type> > detectors) {
    this->detectors = detectors;

}

std::vector<dlib::rectangle> DLibProcessor::getObjectedDetectionBoxes(Image8bit image) {

    dlib::cv_image<unsigned char> img(image);

    std::vector<dlib::rectangle> dets = evaluate_detectors(detectors, img);

    return std::vector<dlib::rectangle>();

}
