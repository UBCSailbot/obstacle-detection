//
// Created by paul on 25/01/16.
//

#include "HorizonImageTest.h"

TEST_F(HorizonImageTest, perfectlyLevel) {
    HorizonImage hi(Image8bit(60, 80), _factory.makeNeutralHorizon());
    EXPECT_TRUE(hi.calculateCenterLine().isParallelTo(Vector2d(0, 10)));
}

TEST_F(HorizonImageTest, rotated45Deg) {
    HorizonImage hi(Image8bit(60, 80), _factory.makeHorizon(Orientation(M_PI/4, 0, 0)));
    EXPECT_TRUE(hi.calculateCenterLine().isParallelTo(Vector2d(5,-5)));
}


TEST_F(HorizonImageTest, rotatedMinus45Deg) {
    HorizonImage hi(Image8bit(60, 80), _factory.makeHorizon(Orientation(-M_PI/4, 0, 0)));
    EXPECT_TRUE(hi.calculateCenterLine().isParallelTo(Vector2d(-5,-5)));
}

// XXX: The following test has been commented out until a revised implementation of
//       converting orientations into horizon lines is complete. In its stead is another
//       test that circumvents the problems with creating horizons at steep angles.
//TEST_F(HorizonImageTest, rotated90Deg) {
//    HorizonImage hi(Image8bit(60, 80), _factory.makeHorizon(Orientation(M_PI/2, 0, 0)));
//    EXPECT_TRUE(hi.calculateCenterLine().isParallelTo(Vector2d(10,0)));
//}
TEST_F(HorizonImageTest, rotated90Deg) {
    HorizonImage hi(Image8bit(60, 80), Horizon(cv::Point2f(40, 80), cv::Point2f(40, 0)));
    EXPECT_TRUE(hi.calculateCenterLine().isParallelTo(Vector2d(10,0)));
}

// XXX: The following test has been commented out until a revised implementation of
//       converting orientations into horizon lines is complete. In its stead is another
//       test that circumvents the problems with creating horizons at steep angles.
//TEST_F(HorizonImageTest, rotatedMinus90Deg) {
//    HorizonImage hi(Image8bit(60, 80), _factory.makeHorizon(Orientation(-M_PI/2, 0, 0)));
//    EXPECT_TRUE(hi.calculateCenterLine().isParallelTo(Vector2d(-10, 0)));
//}

TEST_F(HorizonImageTest, rotatedMinus90Deg) {
    HorizonImage hi(Image8bit(60, 80), Horizon(cv::Point2f(40, 0), cv::Point2f(40, 80)));
    EXPECT_TRUE(hi.calculateCenterLine().isParallelTo(Vector2d(-10, 0)));
}

// TODO: Figure out boundary cases. Which slopes will be equal?
