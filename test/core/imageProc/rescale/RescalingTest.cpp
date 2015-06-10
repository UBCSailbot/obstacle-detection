//
// Created by paul on 09/06/15.
//

#include "RescalingTest.h"

TEST(RescalingTest, eightBitWindowSizeAssertion) {
    Image16bit src(5,6);
    Image8bit dst(4,5);
    int newMinPixelValue = 1;
    EXPECT_DEATH(Rescaling::rescale8bitWindow(src, dst, newMinPixelValue), "c*");
}