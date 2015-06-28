//
// Created by paul on 12/06/15.
//

#include "Image16bitTest.h"

TEST_F(Image16bitTest, defaultConstructor) {
    Image16bit img;

    EXPECT_EQ(CV_16UC1, img.type());
}

TEST_F(Image16bitTest, constructCopyData) {
    Image16bit img(_m1, true);
    _m1.at<int>(0,0) = 99;

    EXPECT_EQ(99, _m1.at<int>(0,0));
    EXPECT_EQ(1, img.pixelAt(0, 0));
}

TEST_F(Image16bitTest, constructNoCopyData) {
    Image16bit img(_m1, false);
    _m1.at<int>(0,0) = 99;

    EXPECT_EQ(99, _m1.at<int>(0,0));
    EXPECT_EQ(99, img.pixelAt(0, 0));
}

TEST_F(Image16bitTest, assert16bit) {
    cv::Mat m(5,5,CV_8UC1);

    EXPECT_DEATH(Image16bit img(m, true), "c*");
}

TEST_F(Image16bitTest, force16bit) {
    cv::Mat m;

    EXPECT_EQ(0, m.type());

    Image16bit::forceConversion(m);

    EXPECT_EQ(CV_16UC1, m.type());
}

Image16bitTest::Image16bitTest() {
    uint16_t* data = (uint16_t *) malloc( sizeof(uint16_t) * _size1);
    for (uint16_t i=1; i < _size1; i++) {
        data[i-1] = i;
    }

    _m1 = cv::Mat(1, _size1, CV_16UC1, data);
}
