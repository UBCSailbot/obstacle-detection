#ifndef SUNIMG_H
#define SUNIMG_H

#include "opencv2/features2d/features2d.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <limits>

#include "geometry/Horizon.h"
#include "common/Rect2f.h"

class SunImage
{
public:
    SunImage(const Horizon &horizon, const cv::Mat &frame, unsigned int minSunPixelValue, float margin);
    ~SunImage();

    void findSunPosition();
    Rect2f getSunPosition() const;

    void findColumn();
    Line* getLeftMargin() const;
    Line* getRightMargin() const;

    void findMeanVariance();
    float getMean() const;
    float getVariance() const;

private:
    const Horizon _horizon;
    cv::Mat _frame;
    const unsigned int _minSunPixelValue;
    const float _margin;

    Rect2f _sunPosition = Rect2f(-1.0, -1.0, -1.0, -1.0);

    float _mean = 0.0;
    float _variance = 0.0;

    Line* leftMargin = new Line(cv::Point2f(-1.0, -1.0), cv::Point2f(-1.0, -1.0));
    Line* rightMargin = new Line(cv::Point2f(-1.0, -1.0), cv::Point2f(-1.0, -1.0));

//    unsigned int _sunLeft = std::numeric_limits<unsigned int>::max();
//    unsigned int _sunRight = 0;
//    unsigned int _sunTop = std::numeric_limits<unsigned int>::max();
//    unsigned int _sunBottom = 0;

    cv::Point2f _leftDelimTop;
    cv::Point2f _leftDelimBottom;
    cv::Point2f _rightDelimTop;
    cv::Point2f _rightDelimBottom;
};

#endif
