//
// Created by paul on 01/06/15.
//

#include "ClippingRescaler.h"

ClippingRescaler::ClippingRescaler(HistogramGenerator *histogramGenerator,
                                             CentralTendencyGetter *centralTendencyGetter) :
        _histogramGenerator(histogramGenerator),
        _centralTendencyGetter(centralTendencyGetter)
{

}

ClippingRescaler::~ClippingRescaler() {
    delete _histogramGenerator;
    delete _centralTendencyGetter;
}

void ClippingRescaler::scale16bitTo8bit(const Image16bit &src, Image8bit &dst) {
    ImageHistogram histogram = _histogramGenerator->generateHistogram(src);

    int localPeakValue = _centralTendencyGetter->getCentralTendency(histogram);

    //Rescaling::clipTo8bitsCompress2to1(src, dst, localPeakValue);
    Rescaling::clipTo8bitsNoCompression(src, dst, localPeakValue);

}

