#ifndef SUNIMG_H
#define SUNIMG_H

#include "../horizon/Horizon.h"

#include "opencv2/features2d/features2d.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <limits>

class SunImage
{
public:
    SunImage(const Horizon &horizon, const cv::Mat &frame, unsigned int minSunPixelValue, int margin);
    ~SunImage();

private:
    void findSun();
    //unsigned int sunRadius();

    //Rect isSun();   //OpenCV doesn't have a circle class

    const Horizon horizon;
    cv::Mat frame;
    const unsigned int minSunPixelValue;
    const unsigned int margin;

    unsigned int sunRadius;
    unsigned int sunLeft = std::numeric_limits<unsigned int>::max();
    unsigned int sunRight = 0;
    unsigned int sunTop = std::numeric_limits<unsigned int>::max();
    unsigned int sunBottom = 0;

    cv::Point2f leftDelimTop;
    cv::Point2f leftDelimBottom;
    cv::Point2f rightDelimTop;
    cv::Point2f rightDelimBottom;
};

#endif
