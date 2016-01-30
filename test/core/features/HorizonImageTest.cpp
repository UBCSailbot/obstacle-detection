//
// Created by paul on 25/01/16.
//

#include <features/HorizonImage.h>
#include "HorizonImageTest.h"

TEST_F(HorizonImageTest, perfectlyLevel) {
    HorizonImage hi(Image8bit(60, 80), _factory.makeNeutralHorizon());
    EXPECT_FLOAT_EQ(Line(cv::Point2f(0,0), cv::Point2f(0,10)).calculateSlope(),
                    hi.calculateCenterLine().calculateSlope());
}

TEST_F(HorizonImageTest, rotated45Deg) {
    HorizonImage hi(Image8bit(60, 80), _factory.makeHorizon(Orientation(M_PI/4, 0, 0)));
    EXPECT_FLOAT_EQ(Line(cv::Point2f(0,0), cv::Point2f(5,-5)).calculateSlope(),
                    hi.calculateCenterLine().calculateSlope());
}


TEST_F(HorizonImageTest, rotatedMinus45Deg) {
    HorizonImage hi(Image8bit(60, 80), _factory.makeHorizon(Orientation(-M_PI/4, 0, 0)));
    EXPECT_FLOAT_EQ(Line(cv::Point2f(0,0), cv::Point2f(-5, -5)).calculateSlope(),
                    hi.calculateCenterLine().calculateSlope());
}

TEST_F(HorizonImageTest, rotated90Deg) {
    HorizonImage hi(Image8bit(60, 80), _factory.makeHorizon(Orientation(M_PI/2, 0, 0)));
    EXPECT_FLOAT_EQ(Line(cv::Point2f(0,0), cv::Point2f(10, 0)).calculateSlope(),
                    hi.calculateCenterLine().calculateSlope());
}

TEST_F(HorizonImageTest, rotatedMinus90Deg) {
    HorizonImage hi(Image8bit(60, 80), _factory.makeHorizon(Orientation(-M_PI/2, 0, 0)));
    EXPECT_FLOAT_EQ(Line(cv::Point2f(0,0), cv::Point2f(-10, 0)).calculateSlope(),
                    hi.calculateCenterLine().calculateSlope());
}

// TODO: Figure out boundary cases. Which slopes will be equal?
