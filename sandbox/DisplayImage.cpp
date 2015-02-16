#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <string>

#include "DisplayImage.h"

int displayImage(std::string argv ) {

    cv::Mat image = cv::imread( argv, 1 );

    if ( !image.data ) {
        printf("No image data \n");
        return -1;
    }

    cv::imshow("Display Image", image);
    cv::waitKey(0);

    return 0;
}

void test_displayImage() {
	std::string img_path = "/home/paul/Desktop/vision/c-tutorial/res/lena.png";
	displayImage(img_path);
}
