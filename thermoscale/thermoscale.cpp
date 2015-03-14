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

#define APP_NAME "thermoscale"
#define WIN_ZOOM_FACTOR 8
#define WIN_WIDTH 80 * WIN_ZOOM_FACTOR
#define WIN_HEIGHT 60 * WIN_ZOOM_FACTOR
#define EIGHT_BITS 256

struct TrackbarInfo {
    int minVal_orig;
    int* trackbarMin;
    int* trackbarMax; 
};

struct TrackbarInfo* newTrackbarInfo(int minVal_orig, int* trackbarMin, int* trackbarMax) {
    struct TrackbarInfo* info = (TrackbarInfo*) malloc(sizeof(struct TrackbarInfo));
    info->minVal_orig = minVal_orig;
    info->trackbarMin = trackbarMin;
    info->trackbarMax = trackbarMax;
    return info;
}

int trackbarValToPixelVal(int trackbarVal, int origMinVal) {
    return trackbarVal - EIGHT_BITS/2 + origMinVal;
}

static void onMouse( int event, int x, int y, int, void* imgVP)
{
    if( event != cv::EVENT_LBUTTONDOWN )
        return;

    cv::Mat* img = static_cast<cv::Mat*>(imgVP);
    int pixelVal = img->at<uint16_t>(y/WIN_ZOOM_FACTOR, x/WIN_ZOOM_FACTOR);
    
    std::cout << "Pixel value: " << pixelVal << std::endl;
}

void onTrackbarSlide(int pos, void* VP) {
    struct TrackbarInfo* info = static_cast<struct TrackbarInfo*>(VP);

    int minVal_orig = info->minVal_orig;
    int cur_min = trackbarValToPixelVal(*(info->trackbarMin), minVal_orig);
    int cur_max = trackbarValToPixelVal(*(info->trackbarMax), minVal_orig);

    std::cout << "Min threshold: " << cur_min << std::endl;
    std::cout << "Max threshold: " << cur_max << std::endl;
    std::cout << "Range: " << cur_max - cur_min << std::endl << std::endl;
}

int main( int argc, char** argv ) {

    if(argc != 2) {
        std::cout << "Usage: " << APP_NAME << " <image path>" << std::endl;
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
    std::string win_name = APP_NAME;
    win_name += ": " + image_path;
    cv::namedWindow(win_name);
    int minVal_trackbar = 128;
    int maxVal_trackbar = range + 128; 
    struct TrackbarInfo* info = newTrackbarInfo(minVal_orig, &minVal_trackbar, &maxVal_trackbar);

    cv::createTrackbar("Min", win_name, &minVal_trackbar, range + 256, onTrackbarSlide, info);
    cv::createTrackbar("Max", win_name, &maxVal_trackbar, range + 256, onTrackbarSlide, info);
    cv::setMouseCallback( win_name, onMouse, &image);

    // Dynamically adjust min and max pixel intensity values using window sliders    
    while (true) {

        // Convert to real pixel intensity values
        // TODO: handle boundary cases (ensure values are never < 0 or > UINT16_MAX)
        int minVal = trackbarValToPixelVal(minVal_trackbar, minVal_orig);
        int maxVal = trackbarValToPixelVal(maxVal_trackbar, minVal_orig);

        // Convert input image to 8-bit and resize
        image.convertTo(eightBit, CV_8UC1, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
        cv::resize(eightBit, displayed, displayed.size(), 0, 0, cv::INTER_NEAREST);

        // Display processed image
        cv::imshow(win_name, displayed);
        char c = cv::waitKey(33);  // wait 33 ms to show frame
        if (c == 27 || c == 113)
            break;  // break if Esc key or Q key are hit
        
    }
}
