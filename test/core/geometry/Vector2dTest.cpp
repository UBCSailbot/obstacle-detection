//
// Created by paul on 30/01/16.
//

#include "Vector2dTest.h"

/**
 * Tests for Vector2d::dotProduct
 */

TEST(Vector2dTest, zeroDotProduct) {
    Vector2d v1(0, 1);
    Vector2d v2(1, 0);
    EXPECT_TRUE(Compare::areMagnitudesEqual(0, v1.dotProduct(v2)));
}

TEST(Vector2dTest, dotProductAssociativity) {
    Vector2d v1(3, 7);
    Vector2d v2(-2, 6);
    EXPECT_TRUE(Compare::areMagnitudesEqual(v1.dotProduct(v2), v2.dotProduct(v1)));
}

TEST(Vector2dTest, dotProduct) {
    Vector2d v1(2, -3);
    Vector2d v2(-7, 8);
    EXPECT_TRUE(Compare::areMagnitudesEqual(2 * (-7) + (-3) * 8, v1.dotProduct(v2)));
}


/**
 * Tests for Vector2d::angleBetween
 */

TEST(Vector2dTest, angleBetweenAssociativity) {
    Vector2d v1(2, -3);
    Vector2d v2(-7, 8);
    EXPECT_TRUE(Compare::areAnglesEqual(v1.angleBetween(v2), v2.angleBetween(v1)));
}

TEST(Vector2dTest, angleBetweenParallel) {
    Vector2d v1(2, -3);
    Vector2d v2(4, -6);
    EXPECT_TRUE(Compare::areAnglesEqual(0, v1.angleBetween(v2)));
}

TEST(Vector2dTest, angleBetweenOrthogonal) {
    Vector2d v1(-2, 3);
    Vector2d v2(-3, -2);
    EXPECT_TRUE(Compare::areAnglesEqual(M_PI / 2, v1.angleBetween(v2)));
}

TEST(Vector2dTest, angleBetweenZero) {
    Vector2d v1(4, 6);
    Vector2d v2(0, 0);

    EXPECT_THROW(v1.angleBetween(v2), std::invalid_argument);
}

TEST(Vector2dTest, angleBetweenOpposite) {
    Vector2d v1(-2, 3);
    Vector2d v2(2, -3);

    EXPECT_TRUE(Compare::areAnglesEqual(v1.angleBetween(v2), M_PI));
}


/**
 * Tests for Vector2d::isParallelTo
 */

TEST(Vector2dTest, isParallelToSameDirections) {
    Vector2d v(2, 3);
    Vector2d u(4, 6);
    EXPECT_TRUE(v.isParallelTo(u));
    EXPECT_TRUE(u.isParallelTo(v));
}

TEST(Vector2dTest, isParallelToOppositeDirections) {
    Vector2d v(2, 3);
    Vector2d u(-4, -6);
    EXPECT_TRUE(v.isParallelTo(u));
    EXPECT_TRUE(u.isParallelTo(v));
}

TEST(Vector2dTest, isParallelToFail) {
    Vector2d v(-6, 19);
    Vector2d u(1, 1);
    EXPECT_FALSE(v.isParallelTo(u));
    EXPECT_FALSE(u.isParallelTo(v));
}


/**
 * Tests for Vector2d::calculateMagnitude
 */

TEST(Vector2dTest, magnitudeZeroVector) {
    Vector2d z(0, 0);
    EXPECT_TRUE(Compare::areMagnitudesEqual(z.calculateMagnitude(), 0));
}

TEST(Vector2dTest, calculateMagnitudePositiveComponents) {
    Vector2d a(1, 0);
    EXPECT_TRUE(Compare::areMagnitudesEqual(a.calculateMagnitude(), 1));

    a.x = 0; a.y = 1;
    EXPECT_TRUE(Compare::areMagnitudesEqual(a.calculateMagnitude(), 1));

    a.x = 3; a.y = 4;
    EXPECT_TRUE(Compare::areMagnitudesEqual(a.calculateMagnitude(), 5));

    a.x = 4; a.y = 3;
    EXPECT_TRUE(Compare::areMagnitudesEqual(a.calculateMagnitude(), 5));
}

TEST(Vector2dTest, calculateMagnitudeNegativeComponents) {
    Vector2d a(-3, 4);
    EXPECT_TRUE(Compare::areMagnitudesEqual(a.calculateMagnitude(), 5));

    a.x = -4; a.y = 3;
    EXPECT_TRUE(Compare::areMagnitudesEqual(a.calculateMagnitude(), 5));

    a.x = -4; a.y = -3;
    EXPECT_TRUE(Compare::areMagnitudesEqual(a.calculateMagnitude(), 5));

}


/**
 * Tests for Vector2d::multiplyByScalar
 */

TEST(Vector2dTest, multiplyByScalar) {
    Vector2d a(1,2);

    EXPECT_EQ(a.multiplyByScalar(3), Vector2d(3,6));
    EXPECT_EQ(a.multiplyByScalar(-2), Vector2d(-2,-4));
    EXPECT_EQ(a.multiplyByScalar(0), Vector2d(0,0));
}


/**
 * Tests for Vector2d::scalarProjectionOnto
 */

TEST(Vector2dTest, scalarProjectionZeroes) {
    Vector2d v1(4, 6);
    Vector2d v2(0, 0);
    EXPECT_TRUE(Compare::areMagnitudesEqual(0, v1.scalarProjectionOnto(v2)));
    EXPECT_TRUE(Compare::areMagnitudesEqual(0, v2.scalarProjectionOnto(v1)));
}

TEST(Vector2dTest, scalarProjectionOntoBases) {
    Vector2d v(-7, 13);
    Vector2d x(1, 0);
    Vector2d y(0, 1);

    EXPECT_TRUE(Compare::areMagnitudesEqual(v.scalarProjectionOnto(x), -7));
    EXPECT_TRUE(Compare::areMagnitudesEqual(v.scalarProjectionOnto(y), 13));
}

TEST(Vector2dTest, scalarProjectionOntoParallel) {
    Vector2d u(1, -1);
    Vector2d v(2, -2);

    EXPECT_TRUE(Compare::areMagnitudesEqual(u.scalarProjectionOnto(v), pow(2, 0.5)));
}

TEST(Vector2dTest, scalarProjectionOntoItself) {
    Vector2d a(-97, 101);

    EXPECT_TRUE(Compare::areMagnitudesEqual(a.scalarProjectionOnto(a), a.calculateMagnitude()));
}

/**
 * Tests for Vector2d::vectorProjectionOnto
 */

TEST(Vector2dTest, vectorProjectionOntoZero) {
    Vector2d v(4, 6);
    Vector2d z(0, 0);
    EXPECT_EQ(z, v.vectorProjectionOnto(z));
}

TEST(Vector2dTest, vectorProjectionOntoItself) {
    Vector2d v(3, -11);

    EXPECT_EQ(v, v.vectorProjectionOnto(v));
}

TEST(Vector2dTest, vectorProjectionOntoOrthogonal) {
    Vector2d v(16, 24);
    Vector2d u(-24, 16);

    EXPECT_EQ(Vector2d(0, 0), v.vectorProjectionOnto(u));
    EXPECT_EQ(Vector2d(0, 0), u.vectorProjectionOnto(v));
}

TEST(Vector2dTest, vectorProjectionOntoTypical) {
    Vector2d u(-1, -7);
    Vector2d v(-8, -6);

    EXPECT_EQ(Vector2d(-4, -3), u.vectorProjectionOnto(v));
}


/**
 * Tests for Vector2d::calculateUnitVector
 */

TEST(Vector2dTest, unitVectorFailForZero) {
    EXPECT_THROW(Vector2d(0, 0).calculateUnitVector(), std::invalid_argument);
}

TEST(Vector2dTest, unitVectorSelf) {
    Vector2d u(pow(2, 0.5) / 2, pow(2, 0.5) / 2);

    EXPECT_EQ(u, u.calculateUnitVector());
}

TEST(Vector2dTest, unitVectorBases) {
    Vector2d x(111, 0);
    Vector2d y(0, -6983);

    EXPECT_EQ(x.calculateUnitVector(), Vector2d(1, 0));
    EXPECT_EQ(y.calculateUnitVector(), Vector2d(0, -1));
}


/**
 * Tests for Vector2d::isZeroVector
 */

TEST(Vector2dTest, isZeroVector) {
    EXPECT_TRUE(Vector2d(0, 0).isZeroVector());
    EXPECT_FALSE(Vector2d(1, 1).isZeroVector());
}

/**
 * Tests for Vector2d::operator==
 */
TEST(Vector2dTest, equality) {
    EXPECT_EQ(Vector2d(0, 0), Vector2d(0, 0));
    EXPECT_FALSE(Vector2d(1, 0) == Vector2d(0, 0));

    // Negatives of vectors are not equal
    EXPECT_EQ(Vector2d(1, 0), Vector2d(1, 0));
    EXPECT_FALSE(Vector2d(1, 0) == Vector2d(-1, 0));
    EXPECT_EQ(Vector2d(0, 1), Vector2d(0, 1));
    EXPECT_FALSE(Vector2d(0, 1) == Vector2d(0, -1));
}
