//
// Created by paul on 07/06/15.
//

#include "ValueSmootherTest.h"

TEST(ValueSmootherTest, simpleSmoothing) {
    int bufferSize = 10;
    ValueSmoother v(bufferSize);

    for (int i = 0; i < bufferSize + 1; i++) {
        int result = v.calculateSmoothedValue(i);
        if (i <= bufferSize) {
            EXPECT_EQ(i, result);
        }
        else {
            EXPECT_EQ(i * (i + 1) / 2, result);
        }
    }

}