//
// Created by paul on 28/05/15.
//

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;



int main() {
    Mat displayed = Mat::zeros(60, 80, CV_8UC3);
    line(displayed, Point2f(40,60), Point2f(80, 40), Scalar(255,0,0), 1);
    displayed.at<Vec3b>(55, 76)[0] = 255;
    displayed.at<Vec3b>(55, 76)[1] = 0;
    displayed.at<Vec3b>(55, 76)[2] = 0;
    displayed.at<Vec3b>(59, 30)[0] = 0;
    displayed.at<Vec3b>(59, 30)[1] = 0;
    displayed.at<Vec3b>(59, 30)[2] = 255;
    resize(displayed, displayed, Size(400,300), 0, 0, cv::INTER_NEAREST);
    imshow("dummyWindow", displayed);
    waitKey(0);
}