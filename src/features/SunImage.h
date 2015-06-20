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
    SunImage(const Horizon &horizon, const cv::Mat &frame, unsigned int minSunPixelValue, float margin);
    ~SunImage();

    void findPosition();
    void findMeanVariance();
    void findColumn();

    cv::Point2f getPosition() const;
    float getMean() const;
    float getVariance() const;
    Line getLeftMargin() const;
    Line getRightMargin() const;

private:

    //unsigned int sunRadius();
    //Rect isSun();   //OpenCV doesn't have a circle class

    const Horizon _horizon;
    cv::Mat _frame;
    const unsigned int _minSunPixelValue;
    const float _margin;

    //unsigned int sunRadius;
//    bool hasSun = false;

    unsigned int _sunLeft = std::numeric_limits<unsigned int>::max();
    unsigned int _sunRight = 0;
    unsigned int _sunTop = std::numeric_limits<unsigned int>::max();
    unsigned int _sunBottom = 0;
//    cv::Point2f sunPosition;

    float _mean = 0.0;
    float _variance = 0.0;
    
    cv::Point2f _leftDelimTop;
    cv::Point2f _leftDelimBottom;
    cv::Point2f _rightDelimTop;
    cv::Point2f _rightDelimBottom;

//    Line leftDelim(cv::Point2f(), cv::Point2f());
//    Line::Line rightDelim;
};

#endif
