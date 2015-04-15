#ifndef SUNIMG_H
#define SUNIMG_H

#include "Horizon.h";
#include "vmath.h";

class SunImage
{
public:
    SunImage(Horizon horizon, cv::Mat frame, int minSunPixelValue, int margin);

private:
    //leftDelim
    //rightDelim
}

#endif
