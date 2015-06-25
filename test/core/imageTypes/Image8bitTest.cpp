//
// Created by paul on 14/06/15.
//

#include "Image8bitTest.h"

TEST_F(Image8bitTest, defaultConstructor) {
    Image8bit img;

    EXPECT_EQ(CV_8UC1, img.type());
}

TEST_F(Image8bitTest, constructCopyData) {
    Image8bit img(_m1, true);
    _m1.at<uint8_t>(0,0) = 99;

    EXPECT_EQ(99, _m1.at<uint8_t>(0,0));
    EXPECT_EQ(1, img.pixelAt(0, 0));
}

TEST_F(Image8bitTest, constructNoCopyData) {
    Image8bit img(_m1, false);
    _m1.at<uint8_t>(0,0) = 99;

    EXPECT_EQ(99, _m1.at<uint8_t>(0,0));
    EXPECT_EQ(99, img.pixelAt(0,0));
}

TEST_F(Image8bitTest, assert8bit) {
    cv::Mat m(5,5,CV_16UC1);

    EXPECT_DEATH(Image8bit img(m, true), "c*");
}

TEST_F(Image8bitTest, force16bit) {
    cv::Mat m;

    EXPECT_EQ(0, m.type());

    Image8bit::forceConversion(m);

    EXPECT_EQ(CV_8UC1, m.type());
}

Image8bitTest::Image8bitTest() {
    uint8_t* data = (uint8_t *) malloc( sizeof(uint8_t) * _size1);
    for (uint8_t i=0; i < _size1; i++) {
        data[i-1] = i;
    }

    _m1 = cv::Mat(1, _size1, CV_8UC1, data);
}

