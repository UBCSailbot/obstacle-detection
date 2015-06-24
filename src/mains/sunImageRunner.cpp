//
// Created by delun on 16/06/15.
//

#include "../features/SunImage.h"
#include <iostream>

int main(int argc, char** argv) {


    if(argc < 4) {
        std::cout << "Usage: <input_image> <sun_brightness> <margin>" << std::endl;
        return -1;
    }

    cv::Mat grayScale = cv::imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    cv::Mat color = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);

    if(! grayScale.data )
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    Horizon h = Horizon(cv::Point2f (0, 50), cv::Point2f (VIEWPORT_WIDTH_PIX - 1, 50));
    SunImage sunImage = SunImage(h, grayScale, atoi(argv[2]), atof(argv[3]));

    line(color, sunImage.getSunPosition(), sunImage.getSunPosition(), cv::Scalar(0, 0, 0xFFFF));
    line(color, h.getStartPoint(), h.getEndPoint(), cv::Scalar(0xFFFF, 0, 0));
    line(color, sunImage.getGlintLeftMargin().getStartPoint(), sunImage.getGlintLeftMargin().getEndPoint(), cv::Scalar(0, 0xFFFF, 0));
    line(color, sunImage.getGlintRightMargin().getStartPoint(), sunImage.getGlintRightMargin().getEndPoint(), cv::Scalar(0, 0xFFFF, 0));

    resize(color, color, cv::Size(400,300), 0, 0, cv::INTER_NEAREST);
    cv::imshow("windows", color);
    cv::waitKey(0);
}