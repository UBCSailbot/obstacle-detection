//
// Created by denis on 06/02/16.
//

#ifndef OBSTACLE_DETECTION_DLIBPROCESSOR_H
#define OBSTACLE_DETECTION_DLIBPROCESSOR_H


#include <dlib/geometry/rectangle.h>
#include <types/Image8bit.h>
#include <dlib/image_processing/object_detector.h>
#include <dlib/image_transforms/image_pyramid.h>
#include <types/Image16bit.h>
#include <dlib/image_processing/scan_fhog_pyramid.h>

class DLibProcessor {
public:
    typedef dlib::scan_fhog_pyramid<dlib::pyramid_down<6>> image_scanner_type;

    /**
     * This object is for detecting objects using a set of object detectors
   * PARAM: detectors - vector of dlib object detectors of image_scanner_type that can either come from
   * serialized files or are generated.
   */
    DLibProcessor(std::vector<dlib::object_detector<image_scanner_type>> detectors);

    virtual std::vector<cv::Rect> getObjectDetectionBoxes(Image16bit image);

private:
    static cv::Rect dlibRectangleToOpenCV(dlib::rectangle rectangle);

    std::vector<dlib::object_detector<image_scanner_type>> _detectors;

};


#endif //OBSTACLE_DETECTION_DLIBPROCESSOR_H
