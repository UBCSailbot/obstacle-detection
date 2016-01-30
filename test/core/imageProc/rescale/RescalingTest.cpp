//
// Created by paul on 09/06/15.
//

#include <exceptions/ImageSizeMismatchException.h>
#include "RescalingTest.h"

TEST_F(RescalingTest, eightBitWindowSizeAssertion) {
    Image16bit src(5,6);
    Image8bit dst(4,5);
    int newMinPixelValue = 1;
    EXPECT_THROW(Rescaling::clipTo8bitsCompress2to1(src, dst, newMinPixelValue), ImageSizeMismatchException);
}

TEST_F(RescalingTest, testAllValuesNoCompression) {
    double min, max;
    // The image we use for this test has a very wide window in 16-bit
    minMaxLoc(_freighterSunImg, &min, &max);
    double avg = (min + max) / 2;

    Image16bit src(_freighterSunImg, false);
    Image8bit dst(_freighterSunImg.rows, _freighterSunImg.cols);
    Rescaling::clipTo8bitsNoCompression(src, dst, (int) avg);

    for (int row = 0; row < src.rows; row++) {
        for (int col = 0; col < src.cols; col++) {
            if (src.pixelAt(row, col) >= avg + 128) {
                EXPECT_EQ(255, dst.pixelAt(row, col));
            }
            else if (src.pixelAt(row, col) <= avg - 127) {
                EXPECT_EQ(0, dst.pixelAt(row, col));
            }
            else {
                EXPECT_EQ(src.pixelAt(row, col) - avg + 127, dst.pixelAt(row, col));
            }
        }
    }
}

TEST_F(RescalingTest, testAllValuesCompress2to1) {
    double min, max;
    // The image we use for this test has a very wide window in 16-bit
    minMaxLoc(_freighterSunImg, &min, &max);
    double avg = (min + max) / 2;

    Image16bit src(_freighterSunImg, false);
    Image8bit dst(_freighterSunImg.rows, _freighterSunImg.cols);
    Rescaling::clipTo8bitsCompress2to1(src, dst, (int) avg);

    for (int row = 0; row < src.rows; row++) {
        for (int col = 0; col < src.cols; col++) {
            if (src.pixelAt(row, col) >= avg + 256) {
                EXPECT_EQ(255, dst.pixelAt(row, col));
            }
            else if (src.pixelAt(row, col) <= avg - 255) {
                EXPECT_EQ(0, dst.pixelAt(row, col));
            }
            else {
                EXPECT_EQ((int)(src.pixelAt(row, col) - avg + 255)/2, dst.pixelAt(row, col));
            }
        }
    }
}

// TODO: add a test for at least one boundary case