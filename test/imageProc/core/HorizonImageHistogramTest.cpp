//
// Created by paul on 01/06/15.
//

#include "HorizonImageHistogramTest.h"

static const int imageRows = 60;
static const int imageCols = 80;

TEST_F(HorizonImageHistogramTest, numPixelsHalfFrame) {
    cv::Mat zeros = cv::Mat(imageRows, imageCols, CV_16UC1, cv::Scalar(0));

    // horizon is below entire frame
    Horizon horizon(cv::Point2f(0, imageRows / 2 ), cv::Point2f(imageCols, imageRows / 2));

    HorizonImageHistogram histogram(zeros, horizon);
    EXPECT_EQ(imageCols * imageRows / 2, histogram.getNumPixels());
}