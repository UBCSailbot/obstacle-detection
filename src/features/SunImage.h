#ifndef SUNIMG_H
#define SUNIMG_H

#include "opencv2/features2d/features2d.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <limits>

#include "lepton/LeptonCameraDimensions.h"
#include <iostream>
#include <stack>

#include "geometry/Horizon.h"

class SunImage
{
public:
    SunImage(const Horizon &horizon, const cv::Mat &frame,
             unsigned int minSunPixelValue=DEFAULT_MIN_SUN_PIXEL_VALUE,
             float margin=DEFAULT_MARGIN);

    ~SunImage();

    /**
     * RETURN: Whether or not the sun is visible within the frame.
     */
    bool isSunInFrame() const;

    /**
     * RETURN: Whether or not the water is reflecting sunlight.
     */
    bool isGlintInFrame() const;

    /**
     * RETURN: A point indicating the center of the sun in the frame.
     *  If there is no sun in the frame, returns an empty point.
     */
    cv::Point2f getSunPosition() const;

    /**
     * RETURN: The left margin of the column containing sun glint in
     *  the frame.
     */
    Line getGlintLeftMargin() const;

    /**
     * RETURN: The right margin of the column containing sun glint in
     *  the frame.
     */
    Line getGlintRightMargin() const;

    float getMean();
    float getVariance();

    static const unsigned int DEFAULT_MIN_SUN_PIXEL_VALUE = 8500;
    static constexpr float DEFAULT_MARGIN = 1.5;

private:

    //unsigned int sunRadius();

    void calcSunPosition();
    void calcGlintColumn();

    void calcMeanVariance();

    const Horizon _horizon;
    cv::Mat _frame;
    const unsigned int _minSunPixelValue;
    const float _margin;

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
