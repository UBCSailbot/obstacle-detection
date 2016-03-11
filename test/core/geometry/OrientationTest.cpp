#include "OrientationTest.h"

TEST(OrientationTest, dataString) {
    Orientation o(1.0, 2.0, 3.0);

    EXPECT_EQ("1 2 3\n", o.toDataString());
}

TEST(OrientationTest, radToDeg) {
    Orientation o(1.0, 2.0, 3.0);

    double radToDeg = 180 / M_PI;

    EXPECT_TRUE(Compare::areAnglesEqual(radToDeg, o.rollDegrees));
    EXPECT_TRUE(Compare::areAnglesEqual(2*radToDeg, o.pitchDegrees));
    EXPECT_TRUE(Compare::areAnglesEqual(3*radToDeg, o.yawDegrees));
}