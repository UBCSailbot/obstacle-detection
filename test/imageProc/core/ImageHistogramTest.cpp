//
// Created by paul on 26/05/15.
//

#include "ImageHistogramTest.h"

static const int imageRows = 60;
static const int imageCols = 80;

TEST_F(ImageHistogramTest, numPixelsWholeFrame) {
    cv::Mat zeros = cv::Mat(imageRows, imageCols, CV_16UC1, cv::Scalar(0));

    ImageHistogram histogram(zeros);
    EXPECT_EQ(imageCols * imageRows, histogram.getNumPixels());
}


TEST_F(ImageHistogramTest, statsSinglePixelValue) {
    cv::Mat allPixels7 = cv::Mat(imageRows, imageCols, CV_16UC1, cv::Scalar(7));
    ImageHistogram histogram(allPixels7);

    EXPECT_EQ(7, histogram.getMode());
    EXPECT_EQ(7, histogram.getMedian());
}

TEST_F(ImageHistogramTest, statsThreeEvenPixelValues) {
    cv::Mat image = makeThreeEvenPixelValues(1,2,3);
    ImageHistogram histogram(image);

    EXPECT_EQ(2, histogram.getMedian());
}

TEST_F(ImageHistogramTest, statsFourPixels) {
    std::vector<int> data = {0,1,2,3};
    cv::Mat image(data, false);
    ImageHistogram histogram(image);

    EXPECT_EQ(1, histogram.getMedian());
    EXPECT_EQ(0, histogram.getMode());
}

TEST_F(ImageHistogramTest, statsGaussianDistributionOdd) {
    std::vector<int> data = {0,
                             1,1,
                             2,2,2,2,
                             3,3,3,
                             4,4,
                             5,
                             6,
                             7
    };
    cv::Mat image(data, false);
    ImageHistogram histogram(image);

    EXPECT_EQ(3, histogram.getMedian());
    EXPECT_EQ(2, histogram.getMode());
}

TEST_F(ImageHistogramTest, statsGaussianDistributionEven) {
    std::vector<int> data = {0,
                             1,1,
                             2,2,2,2,
                             3,3,3,
                             4
    };
    cv::Mat image(data, false);
    ImageHistogram histogram(image);

    EXPECT_EQ(2, histogram.getMedian());
    EXPECT_EQ(2, histogram.getMode());
}

TEST_F(ImageHistogramTest, statsBimodalDistributionOdd) {
    std::vector<int> data = {0,0,0,0,
                             1,1,
                             2,2,
                             3,
                             4,4,
                             5,5,
                             6,6,6,6
    };
    cv::Mat image(data, false);
    ImageHistogram histogram(image);

    EXPECT_EQ(3, histogram.getMedian());
    EXPECT_EQ(0, histogram.getMode());
}

TEST_F(ImageHistogramTest, statsBimodalDistributionEven) {
    std::vector<int> data = {0,0,0,0,
                             1,1,
                             2,2,
                             3,
                             4,4,
                             5,5,
                             6,6,6,6,6
    };
    cv::Mat image(data, false);
    ImageHistogram histogram(image);

    EXPECT_EQ(3, histogram.getMedian());
    EXPECT_EQ(6, histogram.getMode());
}


TEST_F(ImageHistogramTest, getMinMaxPixelValues) {
    // TODO: implement this test
}

TEST_F(ImageHistogramTest, numBins) {
    // TODO: implement this test
}


TEST_F(ImageHistogramTest, find8bitWindow) {
    // TODO: implement this test
}


TEST_F(ImageHistogramTest, getNumPixelsWithValue) {
    // TODO: implement this test
}

cv::Mat ImageHistogramTest::makeThreeEvenPixelValues(const int &pixelValue0,
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
