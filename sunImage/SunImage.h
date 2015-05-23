#ifndef SUNIMG_H
#define SUNIMG_H

#include "Horizon.h";
#include "vmath.h";

#include "opencv2/features2d/features2d.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class SunImage
{
public:
    SunImage(Horizon horizon, cv::Mat frame, uint minSunPixelValue, int margin);

private:
    cv::Point2f isSun();
    //Rect isSun();   //OpenCV doesn't have a circle class

    uint sunRadius();

    uint minSunPixelValue;
    uint sunRadius;
    cv::Point2f leftDelimTop;
    cv::Point2f leftDelimBottom;
    cv::Point2f rightDelimTop;
    cv::Point2f rightDelimBottom;
};

#endif
