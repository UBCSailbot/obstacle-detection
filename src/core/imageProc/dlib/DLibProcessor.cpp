#include <dlib/opencv/cv_image.h>
#include <types/Image16bit.h>
#include "DLibProcessor.h"

DLibProcessor::DLibProcessor(std::vector<dlib::object_detector<image_scanner_type>> detectors) : _detectors(detectors) { }

std::vector<cv::Rect> DLibProcessor::getObjectDetectionBoxes(Image16bit image) {
    dlib::cv_image<uint16_t> dlibImage(image);

    std::vector<dlib::rectangle> detectedRectangles = evaluate_detectors(_detectors, dlibImage);
    std::vector<cv::Rect> cvDetectedRectangles;

    std::transform(detectedRectangles.begin(), detectedRectangles.end(), std::back_inserter(cvDetectedRectangles),
                   [](dlib::rectangle elem) { return dlibRectangleToOpenCV(elem); });
    return cvDetectedRectangles;
}

cv::Rect DLibProcessor::dlibRectangleToOpenCV(dlib::rectangle rectangle) {
    return cv::Rect(cv::Point2f(rectangle.left(), rectangle.top()),
                    cv::Point2f(rectangle.right() + 1, rectangle.bottom() + 1));

}