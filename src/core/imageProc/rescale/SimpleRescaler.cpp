//
// Created by paul on 12/05/15.
//

#include "SimpleRescaler.h"

SimpleRescaler::SimpleRescaler() {

}

SimpleRescaler::~SimpleRescaler() {

}

void SimpleRescaler::scale16bitTo8bit(const Image16bit &src, Image8bit &dst) {
    double minVal, maxVal;
    cv::minMaxLoc(src, &minVal, &maxVal);
    src.convertTo(dst, 8, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
}
