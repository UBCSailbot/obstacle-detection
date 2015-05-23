#ifndef SUNIMG_H
#define SUNIMG_H

#include "Horizon.h";
#include "vmath.h";

#include "opencv2/features2d/features2d.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <limits>

class SunImage
{
public:
    SunImage(const Horizon &horizon, cv::Mat &frame, uint minSunPixelValue, int margin) : &horizon(horizon), &frame(frame), minSunPixelValue(minSunPixelValue), margin(margin);

private:
    void findSun();
    //unsigned int sunRadius();

    //Rect isSun();   //OpenCV doesn't have a circle class

    const Horizon &horizon;
    const cv::Mat &frame;
    const unsigned int minSunPixelValue;
    const unsigned int margin;

    unsigned int sunRadius;
    cv::Point2i sunLeft = std::numeric_limits<int>::max();
    cv::Point2i sunRight = 0;
    cv::Point2i sunTop = std::numeric_limits<int>::max();
    cv::Point2i sunBottom = 0;

    cv::Point2f leftDelimTop;
    cv::Point2f leftDelimBottom;
    cv::Point2f rightDelimTop;
    cv::Point2f rightDelimBottom;
};

#endif
