//
// Created by paul on 09/06/15.
//

#include "RescalingTest.h"

TEST_F(RescalingTest, eightBitWindowSizeAssertion) {
    Image16bit src(5,6);
    Image8bit dst(4,5);
    int newMinPixelValue = 1;
    EXPECT_DEATH(Rescaling::clipTo8bits(src, dst, newMinPixelValue), "c*");
}

TEST_F(RescalingTest, testAllValues) {
    double min, max;
    // The image we use for this test has a very wide window in 16-bit
    minMaxLoc(_freighterSunImg, &min, &max);

    Image16bit src(_freighterSunImg, false);
    Image8bit dst(_freighterSunImg.rows, _freighterSunImg.cols);
    Rescaling::clipTo8bits(src, dst, (int) min);

    for (int row = 0; row < src.rows; row++) {
        for (int col = 0; col < src.cols; col++) {
            if (src.pixelAt(row, col) >= min + 255) {
                EXPECT_EQ(255, dst.pixelAt(row, col));
            }
            else if (src.pixelAt(row, col) <= min) {
                EXPECT_EQ(0, dst.pixelAt(row, col));
            }
            else {
                EXPECT_EQ(src.pixelAt(row, col) - min, dst.pixelAt(row, col));
            }
        }
    }
}

// TODO: add a test for at least one boundary case