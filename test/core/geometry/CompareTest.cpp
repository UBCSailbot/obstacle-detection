//
// Created by paul on 05/02/16.
//

#include "CompareTest.h"

TEST_F(CompareTest, areAnglesEqualIdentity) {
    EXPECT_TRUE(Compare::areAnglesEqual(0.001, 0.001));
    EXPECT_TRUE(Compare::areAnglesEqual(999, 999));
}

TEST_F(CompareTest, areAnglesEqualPositive) {
    double pi = M_PI;

    EXPECT_TRUE(Compare::areAnglesEqual(pi, pi - testAnglePrecision));
    EXPECT_FALSE(Compare::areAnglesEqual(pi, pi - (2 * testAnglePrecision)));
}

TEST_F(CompareTest, areAnglesEqualNegative) {
    double negPi = -M_PI;

    EXPECT_TRUE(Compare::areAnglesEqual(negPi, negPi - testAnglePrecision));
    EXPECT_FALSE(Compare::areAnglesEqual(negPi, negPi - (2 * testAnglePrecision)));
}

TEST_F(CompareTest, areCoordinatesEqualIdentity) {
    EXPECT_TRUE(Compare::areCoordinatesEqual(586, 586));
    EXPECT_TRUE(Compare::areCoordinatesEqual(0.01, 0.01));
}

TEST_F(CompareTest, areCoordinatesEqualPositive) {
    double c1 = 5;

    EXPECT_TRUE(Compare::areCoordinatesEqual(c1, c1 + testCoordinatePrecision));
    EXPECT_FALSE(Compare::areCoordinatesEqual(c1, c1 + (2 * testCoordinatePrecision)));
}

TEST_F(CompareTest, areCoordinatesEqualNegative) {
    double c1 = -5;

    EXPECT_TRUE(Compare::areCoordinatesEqual(c1, c1 + testCoordinatePrecision));
    EXPECT_FALSE(Compare::areCoordinatesEqual(c1, c1 + (2 * testCoordinatePrecision)));
}

TEST_F(CompareTest, areMagnitudesEqualIdentity) {
    EXPECT_TRUE(Compare::areMagnitudesEqual(9001, 9001));
    EXPECT_TRUE(Compare::areMagnitudesEqual(0.01, 0.01));
}

TEST_F(CompareTest, areMagnitudesEqualPositive) {
    double c1 = 5;

    EXPECT_TRUE(Compare::areMagnitudesEqual(c1, c1 + testMagnitudePrecision / 2));
    EXPECT_FALSE(Compare::areMagnitudesEqual(c1, c1 + (2 * testMagnitudePrecision)));
}

TEST_F(CompareTest, areMagnitudesEqualNegative) {
    double c1 = -5;

    EXPECT_TRUE(Compare::areMagnitudesEqual(c1, c1 + testMagnitudePrecision / 2));
    EXPECT_FALSE(Compare::areMagnitudesEqual(c1, c1 + (2 * testMagnitudePrecision)));
}