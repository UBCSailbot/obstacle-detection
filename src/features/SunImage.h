#ifndef SUNIMG_H
#define SUNIMG_H

#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <limits>
#include <iostream>
#include <stack>

#include "geometry/Horizon.h"
#include "common/Rect2f.h"
#include "lepton/LeptonCameraDimensions.h"

class SunImage
{
public:
    SunImage(const Horizon &horizon,
             const cv::Mat &frame,
             unsigned int minSunPixelValue = DEFAULT_MIN_SUN_PIXEL_VALUE,
             float margin = DEFAULT_MARGIN);
    ~SunImage();

    void findSunPosition();
    bool containsSun() const;
    Rect2f getSunPosition() const;

    void findGlintColumn();
    Line*getLeftGlintMargin() const;
    Line*getRightGlintMargin() const;

    void findMeanVariance();
    float getMean() const;
    float getVariance() const;

    cv::Mat render() const;

private:
    const Horizon _horizon;
    cv::Mat _frame;
    const unsigned int _minSunPixelValue;
    const float _margin;

    Rect2f _sunPosition = Rect2f(-1.0, -1.0, -1.0, -1.0);

    float _mean = 0.0;
    float _variance = 0.0;

    Line* _leftMargin = new Line(cv::Point2f(-1.0, -1.0), cv::Point2f(-1.0, -1.0));
    Line* _rightMargin = new Line(cv::Point2f(-1.0, -1.0), cv::Point2f(-1.0, -1.0));

    static const unsigned int DEFAULT_MIN_SUN_PIXEL_VALUE = 8500;
    static constexpr float DEFAULT_MARGIN = 1.5;
};

#endif
