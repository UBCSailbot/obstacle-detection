#ifndef SUNIMG_H
#define SUNIMG_H

#include "opencv2/features2d/features2d.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <limits>

#include "geometry/Horizon.h"

class SunImage
{
public:
    SunImage(const Horizon &horizon, const cv::Mat &frame, unsigned int minSunPixelValue, int margin);
    ~SunImage();

    void findSun();
//    void debugMessage();
    void findMeanVariance();

    cv::Point2f getPosition() const;
    float getMean() const;
    float getVariance() const;

private:

    //unsigned int sunRadius();
    //Rect isSun();   //OpenCV doesn't have a circle class

    const Horizon horizon;
    cv::Mat frame;
    const unsigned int minSunPixelValue;
    const unsigned int margin;

    //unsigned int sunRadius;
//    bool hasSun = false;

    unsigned int sunLeft = std::numeric_limits<unsigned int>::max();
    unsigned int sunRight = 0;
    unsigned int sunTop = std::numeric_limits<unsigned int>::max();
    unsigned int sunBottom = 0;
//    cv::Point2f sunPosition;

    float mean = 0.0;
    float variance = 0.0;
    
    cv::Point2f leftDelimTop;
    cv::Point2f leftDelimBottom;
    cv::Point2f rightDelimTop;
    cv::Point2f rightDelimBottom;

//    Line leftDelim(cv::Point2f(), cv::Point2f());
//    Line::Line rightDelim();
};

#endif
