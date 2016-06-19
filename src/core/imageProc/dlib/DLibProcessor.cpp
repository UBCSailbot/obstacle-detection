//
// Created by denis on 06/02/16.
//

#include <dlib/opencv/cv_image.h>
#include <types/Image16bit.h>
#include "DLibProcessor.h"


DLibProcessor::DLibProcessor(std::vector <dlib::object_detector<image_scanner_type>> detectors) : _detectors(detectors) {

}

std::vector<cv::Rect> DLibProcessor::getObjectDetectionBoxes(Image16bit image) {

    std::vector <dlib::rectangle> detectedRecangles = evaluate_detectors(_detectors, image);
    std::vector <cv::Rect> cvDetectedRecangles;

    std::transform(detectedRecangles.begin(), detectedRecangles.end(), std::back_inserter(cvDetectedRecangles), [](dlib::rectangle elem){ return dlibRectangleToOpenCV(elem); });
    return cvDetectedRecangles;
}


static cv::Rect dlibRectangleToOpenCV(dlib::rectangle rectangle)
{
    return cv::Rect(cv::Point2i(rectangle.left(), rectangle.top()), cv::Point2i(rectangle.right() + 1, rectangle.bottom() + 1));
}
