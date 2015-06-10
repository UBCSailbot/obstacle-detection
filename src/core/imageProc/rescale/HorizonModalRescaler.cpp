//
// Created by paul on 23/05/15.
//

#include "HorizonModalRescaler.h"

HorizonModalRescaler::HorizonModalRescaler(int bufferSize) : valueSmoother(bufferSize) {

}

void HorizonModalRescaler::scale16bitTo8bit(const Image16bit &src, const Horizon &horizon, Image8bit &dst) {
    HorizonImageHistogram histogram(src, horizon);
    int localPeakValue = histogram.getMode();
    int bufferedPeakValue = valueSmoother.calculateSmoothedValue(localPeakValue);

    int newMinPixelValue, newMaxPixelValue;
    histogram.find8bitWindow(bufferedPeakValue, newMinPixelValue, newMaxPixelValue);

    Rescaling::rescale8bitWindow(src, dst, newMinPixelValue);
}
