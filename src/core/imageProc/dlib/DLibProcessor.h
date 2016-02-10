//
// Created by denis on 06/02/16.
//

#ifndef OBSTACLE_DETECTION_DLIBPROCESSOR_H
#define OBSTACLE_DETECTION_DLIBPROCESSOR_H


#include <dlib/geometry/rectangle.h>
#include <types/Image8bit.h>
#include <dlib/image_processing/object_detector.h>
#include <dlib/image_transforms/image_pyramid.h>
#include <dlib/image_processing/scan_fhog_pyramid.h>

class DLibProcessor {
public:
    typedef dlib::scan_fhog_pyramid<dlib::pyramid_down<6> > image_scanner_type;

    DLibProcessor(std::vector<dlib::object_detector<image_scanner_type> > detectors);

    virtual std::vector<dlib::rectangle> getObjectedDetectionBoxes(Image8bit image);

private:
    std::vector<dlib::object_detector<image_scanner_type> > detectors;


};


#endif //OBSTACLE_DETECTION_DLIBPROCESSOR_H
