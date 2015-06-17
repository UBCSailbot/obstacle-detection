//
// Created by delun on 16/06/15.
//

#include "../features/SunImage.h"
#include <iostream>

int main(int argc, char** argv) {
    cv::Mat grayScale = cv::imread("resources/img/freighterAndSun01.png", CV_LOAD_IMAGE_UNCHANGED);
    cv::Mat color = cv::imread("resources/img/freighterAndSun01.png", CV_LOAD_IMAGE_COLOR);
    Horizon h = Horizon(cv::Point2f (0, 50), cv::Point2f (VIEWPORT_WIDTH_PIX - 1, 50));
    SunImage sunImage = SunImage(h, grayScale, 9000, 1);
    sunImage.findPosition();
    sunImage.findColumn();

    line(color, sunImage.getPosition(), sunImage.getPosition(), cv::Scalar(0, 0, 0xFFFF));
    line(color, h.getStartPoint(), h.getEndPoint(), cv::Scalar(0xFFFF, 0, 0));
    line(color, sunImage.getLeftMargin().getStartPoint(), sunImage.getLeftMargin().getEndPoint(), cv::Scalar(0, 0xFFFF, 0));
    line(color, sunImage.getRightMargin().getStartPoint(), sunImage.getRightMargin().getEndPoint(), cv::Scalar(0, 0xFFFF, 0));

    resize(color, color, cv::Size(400,300), 0, 0, cv::INTER_NEAREST);
    cv::imshow("windows", color);
    cv::waitKey(0);
}