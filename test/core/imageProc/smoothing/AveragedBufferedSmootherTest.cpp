//
// Created by paul on 07/06/15.
//

#include "AveragedBufferedSmootherTest.h"

TEST_F(AveragedBufferedSmootherTest, singleValue) {
    AveragedBufferedSmoother v(1);
    EXPECT_EQ(10, v.calculateSmoothedValue(10));
}

TEST_F(AveragedBufferedSmootherTest, underCapacity) {
    int bufferSize = 10;
    AveragedBufferedSmoother v(bufferSize);

    int n, result;

    for (n = 1; n <= bufferSize; n++) {
        result = v.calculateSmoothedValue(n);
        EXPECT_EQ((n + 1) / 2, result);
    }
}

TEST_F(AveragedBufferedSmootherTest, simpleSmoothing) {
    int bufferSize = 10;

    /*
     * We provide a few different contiguous test values
     *  to allow for the possibility that our tests could
     *  erroneously pass in spite of off-by-one errors
     *  because of rounding due to integer division.
     */
    AveragedBufferedSmootherTest::testSimpleSmoothing(bufferSize, 100);
    AveragedBufferedSmootherTest::testSimpleSmoothing(bufferSize, 99);
    AveragedBufferedSmootherTest::testSimpleSmoothing(bufferSize, 98);
    AveragedBufferedSmootherTest::testSimpleSmoothing(bufferSize, 97);

}

TEST_F(AveragedBufferedSmootherTest, noSmoothing) {

    int bufferSize = 10;
    AveragedBufferedSmoother v(bufferSize);

    int constantValue = 42;

    for (int i=0; i < bufferSize * 100; i++) {
        v.calculateSmoothedValue(constantValue);
    }

    EXPECT_EQ( constantValue, v.calculateSmoothedValue(constantValue));

}

void AveragedBufferedSmootherTest::testSimpleSmoothing(int bufferSize, int outlier) {
    AveragedBufferedSmoother v(bufferSize);

    int n;

    for (n = 1; n <= bufferSize; n++) {
        v.calculateSmoothedValue(n);
    }
    n--; // to counteract the last n++ of the for loop

    int result = v.calculateSmoothedValue(outlier);
    EXPECT_EQ( (int) ((float) (n + 1)/2 + (float) (outlier - 1)/n ), result);
}