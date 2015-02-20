// To compile:
// g++ scaling.cpp -std=c++11 -o scaling -I/usr/include/opencv -lopencv_core -lopencv_highgui -lopencv_imgproc

/*
TODO

Usability:
-implement this in a nice Java .JAR file for cross-platform compatibility

Features:
-change the sliders to reflect real pixel intensity values (probably requires making a GUI from another external library)
-add a "Save Image" button to save the newly-adjusted image
-add video support for working with a directory full of raw frames

Prettiness:
-in while loop, listen for user adjustment of window size, and resize image accordingly
    -try to center image in displayed window too if it doesn't match image dimensions exactly

*/


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <cstdint>

#define WIN_NAME "Scale 16 to 8-bit"
#define WIN_WIDTH 640
#define WIN_HEIGHT 480


void onTrackbarSlide(int pos) {

}

int greatestOfMinAndZero(int min) {
    if (!min)
        return min;     // return 0 if min is 0
    int unit = min / std::abs(min);  // +1 if min > 0, else -1 
    return (unit - 1) / -2;
}

int main( int argc, char** argv ) {

    if(argc != 2) {
        std::cout << "Usage: scaling <image path>" << std::endl;
        return -1;
    }

    std::string image_path = argv[1];
    cv::Mat image = cv::imread(image_path, -1);

    // Initialize output image containers
    cv::Mat eightBit;
    double minVal_orig;
    double maxVal_orig;
    minMaxLoc(image, &minVal_orig, &maxVal_orig);
    cv::Mat displayed(WIN_HEIGHT, WIN_WIDTH, CV_8UC1);

    int range = maxVal_orig - minVal_orig;

    // Initialize window
    cv::namedWindow(WIN_NAME);
    int minVal_trackbar = 128;
    int maxVal_trackbar = range + 128;    
    cv::createTrackbar("Min", WIN_NAME, &minVal_trackbar, range + 256);
    cv::createTrackbar("Max", WIN_NAME, &maxVal_trackbar, range + 256);

    // Dynamically adjust min and max pixel intensity values using window sliders    
    while (true) {
        // Read trackbar info
        minVal_trackbar = cv::getTrackbarPos("Min", WIN_NAME);
        maxVal_trackbar = cv::getTrackbarPos("Max", WIN_NAME);
    
        // Convert to real pixel intensity values\
        // TODO: handle boundary cases (ensure values are never < 0 or > UINT16_MAX)
        int minVal = minVal_trackbar - 128 + minVal_orig;
        int maxVal = maxVal_trackbar -128 + minVal_orig;
    
        // Convert input image to 8-bit and resize
        image.convertTo(eightBit, CV_8UC1, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
        cv::resize(eightBit, displayed, displayed.size(), 0, 0, cv::INTER_NEAREST);

        // Display processed image
        cv::imshow(WIN_NAME, displayed);
        char c = cv::waitKey(33);  // wait 33 ms to show frame
        if (c == 27)
            break;  // break if Esc key is hit
        
    }
}
