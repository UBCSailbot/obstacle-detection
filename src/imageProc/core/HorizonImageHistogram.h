//
// Created by paul on 23/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_HORIZON_IMAGE_HISTOGRAM_H
#define OBSTACLE_AVOIDANCE_HORIZON_IMAGE_HISTOGRAM_H

#include <opencv2/core/core.hpp>
#include <vector>
#include "../../features/Horizon.h"
#include "ImageHistogram.h"

class HorizonImageHistogram : public ImageHistogram {

public:
    HorizonImageHistogram(const cv::Mat &image, const Horizon &horizon);

private:

    void populateHistogram(const cv::Mat &image, const Horizon &horizon);

};


#endif //OBSTACLE_AVOIDANCE_HORIZON_IMAGE_HISTOGRAM_H
