//
// Created by Derek Lun on 5/23/2015.
//

#include "SunImageTest.h"
#include <iostream>

TEST_F(SunImageTest, test0Pix) {
    cv::Mat zeros = cv::Mat(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX, CV_16UC1, cv::Scalar(0));
    Horizon h = Horizon(cv::Point2f (0, 0), cv::Point2f (VIEWPORT_WIDTH_PIX - 1, 0));
    SunImage sunImage = SunImage(h, zeros, 9000, 1);

    sunImage.findSunColumn();
    EXPECT_EQ(sunImage.getMean(), -1);
    EXPECT_EQ(sunImage.getVariance(), -1);
}

TEST_F(SunImageTest, testMinSunPixelValue) {
    cv::Mat zeros = cv::Mat(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX, CV_16UC1, cv::Scalar(0));
    zeros.at<uint16_t>(20, 20) = 8999;
    Horizon h = Horizon(cv::Point2f (0, 0), cv::Point2f (VIEWPORT_WIDTH_PIX - 1, 0));
    SunImage sunImage = SunImage(h, zeros, 9000, 1);

    sunImage.findSunColumn();
    EXPECT_EQ(sunImage.getMean(), -1);
    EXPECT_EQ(sunImage.getVariance(), -1);
}

TEST_F(SunImageTest, test1PixFlatPointFlatHorizon) {
    cv::Mat zeros = cv::Mat(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX, CV_16UC1, cv::Scalar(0));
    zeros.at<uint16_t>(0, 20) = 9000;
    Horizon h = Horizon(cv::Point2f (0, 0), cv::Point2f (VIEWPORT_WIDTH_PIX - 1, 0));
    SunImage sunImage = SunImage(h, zeros, 9000, 1);

    sunImage.findSunColumn();
    EXPECT_EQ(sunImage.getMean(), 20);
    EXPECT_EQ(sunImage.getVariance(), 0);
}

TEST_F(SunImageTest, test1PixDiagPointFlatHorizon) {
    cv::Mat zeros = cv::Mat(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX, CV_16UC1, cv::Scalar(0));
    zeros.at<uint16_t>(20, 20) = 9000;
    Horizon h = Horizon(cv::Point2f (0, 0), cv::Point2f (VIEWPORT_WIDTH_PIX - 1, 0));
    SunImage sunImage = SunImage(h, zeros, 9000, 1);

    sunImage.findSunColumn();
    EXPECT_EQ(sunImage.getMean(), 20);
    EXPECT_EQ(sunImage.getVariance(), 0);
}

TEST_F(SunImageTest, test1PixFlatPointDiagHorizon) {
    cv::Mat zeros = cv::Mat(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX, CV_16UC1, cv::Scalar(0));
    zeros.at<uint16_t>(0, 20) = 9000;
    Horizon h = Horizon(cv::Point2f (0, 0), cv::Point2f (VIEWPORT_WIDTH_PIX - 1, 59));
    SunImage sunImage = SunImage(h, zeros, 9000, 1);

    sunImage.findSunColumn();
    EXPECT_FLOAT_EQ(sunImage.getMean(), 20*cos(atan(59.0/79.0)));
    EXPECT_EQ(sunImage.getVariance(), 0);
}

TEST_F(SunImageTest, test1PixFlatPointDiagHorizonWithOffSet) {
    cv::Mat zeros = cv::Mat(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX, CV_16UC1, cv::Scalar(0));
    zeros.at<uint16_t>(0, 20) = 9000;
    Horizon h = Horizon(cv::Point2f (0, 59), cv::Point2f (VIEWPORT_WIDTH_PIX - 1, 0));
    SunImage sunImage = SunImage(h, zeros, 9000, 1);

    sunImage.findSunColumn();
    EXPECT_FLOAT_EQ(sunImage.getMean(), pow(pow(20, 2) + pow(59, 2), 0.5)*cos(atan(59.0/20.0) - atan(59.0/79.0)));
    EXPECT_EQ(sunImage.getVariance(), 0);
}