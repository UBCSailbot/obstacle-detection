//
// Created by paul on 26/05/15.
//

#include "HorizonImageHistogramTest.h"

TEST_F(HorizonImageHistogramTest, numPixelsWholeFrame) {
    cv::Mat zeros = cv::Mat(imageRows, imageCols, CV_16UC1, cv::Scalar(0));
    // horizon is below entire frame
    Horizon horizon(cv::Point2f(0, imageRows + 1), cv::Point2f(imageCols, imageRows + 1));

    HorizonImageHistogram histogram(zeros, horizon);
    EXPECT_EQ(imageCols * imageRows, histogram.getNumPixels());
}

TEST_F(HorizonImageHistogramTest, numPixelsHalfFrame) {
    cv::Mat zeros = cv::Mat(imageRows, imageCols, CV_16UC1, cv::Scalar(0));
    // horizon is below entire frame
    Horizon horizon(cv::Point2f(0, imageRows / 2 ), cv::Point2f(imageCols, imageRows / 2));

    HorizonImageHistogram histogram(zeros, horizon);
    EXPECT_EQ(imageCols * imageRows / 2, histogram.getNumPixels());
}


TEST_F(HorizonImageHistogramTest, singlePixelValue) {
    cv::Mat allPixels7 = cv::Mat(imageRows, imageCols, CV_16UC1, cv::Scalar(7));
    HorizonImageHistogram histogram(allPixels7, horizonBelowFrame);

    EXPECT_EQ(7, histogram.getMode());
    EXPECT_EQ(7, histogram.getMedian());
}

TEST_F(HorizonImageHistogramTest, threeEvenPixelValues) {
    cv::Mat image = makeThreeEvenPixelValues(1,2,3);
    HorizonImageHistogram histogram(image, horizonBelowFrame);

    EXPECT_EQ(2, histogram.getMedian());
}


cv::Mat HorizonImageHistogramTest::makeThreeEvenPixelValues(const int &pixelValue0,
                                                            const int &pixelValue1,
                                                            const int &pixelValue2) {
    cv::Mat image(imageRows, imageCols, CV_16UC1);

    int valueSwitch = 0;
    for (int x = 0; x < image.rows; x++) {
        for (int y = 0; y < image.cols; y++) {
            switch (valueSwitch % 3) {
                case 0:
                    image.at<uint16_t>(x, y) = (uint16_t) pixelValue0;
                    break;
                case 1:
                    image.at<uint16_t>(x, y) = (uint16_t) pixelValue1;
                    break;
                case 2:
                    image.at<uint16_t>(x, y) = (uint16_t) pixelValue2;
                    break;
                default:
                    // never reached
                    break;
            }
            valueSwitch ++;
        }
    }

    return image;
}

HorizonImageHistogramTest::HorizonImageHistogramTest()
        : horizonBelowFrame(cv::Point2f(0, imageRows + 1),
                            cv::Point2f(imageCols, imageRows + 1))
{

}
