//
// Created by delun on 16/06/15.
//

#include "../features/SunImage.h"
#include <iostream>

int main(int argc, char** argv) {
    cv::Mat frame = cv::imread("resources/img/freighterAndSun01.png", CV_LOAD_IMAGE_UNCHANGED);
    Horizon h = Horizon(cv::Point2f (0, 50), cv::Point2f (VIEWPORT_WIDTH_PIX - 1, 50));
    SunImage sunImage = SunImage(h, frame, 8150, 1);
    sunImage.findPosition();
    sunImage.findColumn();

    line(frame, sunImage.getPosition(), sunImage.getPosition(), 0);
    line(frame, h.getStartPoint(), h.getEndPoint(), 0);
    line(frame, sunImage.getLeftMargin().getStartPoint(), sunImage.getLeftMargin().getEndPoint(), 0);
    line(frame, sunImage.getRightMargin().getStartPoint(), sunImage.getRightMargin().getEndPoint(), 0);

    resize(frame, frame, cv::Size(400,300), 0, 0, cv::INTER_NEAREST);
    cv::imshow("windows", frame);
    cv::waitKey(0);
}