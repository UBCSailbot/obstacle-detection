//
// Created by denis on 06/02/16.
//

#include <dlib/opencv/cv_image.h>
#include <types/Image16bit.h>
#include "DLibProcessor.h"


DLibProcessor::DLibProcessor(std::vector <dlib::object_detector<image_scanner_type>> detectors) : _detectors(detectors) {

}

std::vector <dlib::rectangle> DLibProcessor::getObjectDetectionBoxes(Image16bit image) {

    dlib::cv_image<uint16_t> img(image);

    std::vector <dlib::rectangle> detectedRecangles = evaluate_detectors(_detectors, img);

    return detectedRecangles;

}
