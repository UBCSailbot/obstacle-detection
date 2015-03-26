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
#include <vector>

#include "thermoscale.hpp"
#include "SelectedPoints.hpp"

SelectedPoints sp;
int EPSILON = 0;

struct TrackbarInfo* newTrackbarInfo(int minVal_orig, int* trackbarMin, int* trackbarMax) {
    struct TrackbarInfo* info = (TrackbarInfo*) malloc(sizeof(struct TrackbarInfo));
    info->minVal_orig = minVal_orig;
    info->trackbarMin = trackbarMin;
    info->trackbarMax = trackbarMax;
    return info;
}

struct ProcessedFrameInfo* newProcessedFrameInfo(cv::Mat* imagePtr, TrackbarInfo* info, std::string* win_name) {
    struct ProcessedFrameInfo* frameInfo = (ProcessedFrameInfo*) malloc(sizeof(struct ProcessedFrameInfo));
    frameInfo->imagePtr = imagePtr;
    frameInfo->trackbarInfo = info;
    frameInfo->win_name = win_name;
    return frameInfo;
}

int trackbarValToPixelVal(int trackbarVal, int origMinVal) {
    return trackbarVal - EIGHT_BITS/2 + origMinVal;
}

cv::Point* getAllSamePixels(cv::Mat* img, int val) {
    cv::Point* points = (cv::Point*) malloc(60 * 80 * sizeof(cv::Point));
    int max_x = img->cols;
    int max_y = img->rows;

    int i = 0;
    for (int x=0; x < max_x; x++) {
        for (int y=0; y < max_y; y++) {
            if (img->at<uint16_t>(y, x) == val) {
                points[i] = cv::Point(x,y);
                i++;
            }
        }
    }

    return points;
}

static void onMouse( int event, int x, int y, int, void* imgVP)
{
    if( event != cv::EVENT_LBUTTONDOWN )
        return;

    cv::Mat* raw_img = static_cast<cv::Mat*>(imgVP);
    int orig_y = y/WIN_ZOOM_FACTOR;
    int orig_x = x/WIN_ZOOM_FACTOR;

    int pixelVal = raw_img->at<uint16_t>(orig_y, orig_x);

    cv::Point* points = (cv::Point*) malloc(60 * 80 * sizeof(cv::Point));
    int max_x = raw_img->cols;
    int max_y = raw_img->rows;

    int i = 0;
    for (int x=0; x < max_x; x++) {
        for (int y=0; y < max_y; y++) {
            int absDiff = std::abs(raw_img->at<uint16_t>(y, x) - pixelVal);
            if (absDiff <= EPSILON) {
                points[i] = cv::Point(x,y);
                i++;
            }
        }
    }

    sp.setPoints(points, i);

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

char showProcessedImage(cv::Mat* raw_image, TrackbarInfo* info, std::string* win_name) {

    // Convert to real pixel intensity values
    // TODO: handle boundary cases (ensure values are never < 0 or > UINT16_MAX)
    int minVal = trackbarValToPixelVal(*(info->trackbarMin), info->minVal_orig);
    int maxVal = trackbarValToPixelVal(*(info->trackbarMax), info->minVal_orig);

    // Convert input image to 8-bit and resize
    cv::Mat eightBit;
    cv::Mat displayed(WIN_HEIGHT, WIN_WIDTH, CV_8UC1);

    raw_image->convertTo(eightBit, CV_8UC3, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
    cv::resize(eightBit, displayed, displayed.size(), 0, 0, cv::INTER_NEAREST);
    cvtColor(displayed, displayed, CV_GRAY2RGB);

    sp.draw(&displayed);

    // Display processed image
    cv::imshow(*win_name, displayed);
    return cv::waitKey(33);  // wait 33 ms to show frame

}

int main( int argc, char** argv ) {

    if(argc != 2) {
        std::cout << "Usage: " << APP_NAME << " <image path>" << std::endl;
        return -1;
    }

    std::string image_path = argv[1];
    cv::Mat raw_image= cv::imread(image_path, -1);

    // Find pixel value range of imageW
    double minVal_orig;
    double maxVal_orig;
    minMaxLoc(raw_image, &minVal_orig, &maxVal_orig);
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
    cv::createTrackbar("Epsilon", win_name, &EPSILON, 128);
    cv::setMouseCallback( win_name, onMouse, &raw_image);

    // Dynamically adjust min and max pixel intensity values using window sliders    
    while (true) {

        char c = showProcessedImage(&raw_image, info, &win_name);
        if (c == 27 || c == 113)
            break;  // break if Esc key or Q key are hit
        if (c == 107)
            

    }
}
