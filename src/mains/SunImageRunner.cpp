//
// Created by delun on 16/06/15.
//

#include "features/SunImage.h"

int main(int argc, char** argv) {


    if(argc < 4) {
        std::cout << "Usage: <input_image> <sun_brightness> <margin>" << std::endl;
        return -1;
    }

    cv::Mat grayScale = cv::imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);

    if(! grayScale.data )
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    Horizon h(cv::Point2f (0, 50), cv::Point2f (VIEWPORT_WIDTH_PIX - 1, 50));
    SunImage sunImage = SunImage(h, grayScale, atoi(argv[2]), atof(argv[3]));

    cv::Mat rendering = sunImage.render();

    resize(rendering, rendering, cv::Size(400,300), 0, 0, cv::INTER_NEAREST);
    cv::imshow("windows", rendering);
    cv::waitKey(0);
}