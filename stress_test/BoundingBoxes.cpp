#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>

//#define DEBUG

using namespace cv;
using namespace std;

int main(int argc, char **argv) {

    String path = argv[1];
    VideoCapture cap(path);

    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "Cannot open the video" << endl;
        return -1;
    }

#ifdef DEBUG
    namedWindow("Obstacles", CV_WINDOW_NORMAL);
    namedWindow("Original", CV_WINDOW_NORMAL);
#endif

    int frame_counter = 1;
    char file_name[50];

    int iLowH = 0;
    int iHighH = 179;

    int iLowS = 0;
    int iHighS = 255;

    int iLowV = 110;
    int iHighV = 255;

    while (true) {
        Mat imgOriginal, imgLap;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

        //if not success, break loop 
        if (!bSuccess) {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        Mat imgHSV;

        //Convert the captured frame from BGR to HSV
        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); 

        Mat imgThresholded, imgThresholded1, imgThresholded2, imgThresholded3, imgThresholded4;
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;


        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

        //morphological opening (remove small objects from the foreground)
        erode(imgThresholded, imgThresholded1, getStructuringElement(MORPH_ELLIPSE, Size(4, 4)));
        dilate(imgThresholded1, imgThresholded2, getStructuringElement(MORPH_ELLIPSE, Size(4, 4)));

        //morphological closing (fill small holes in the foreground)
        dilate(imgThresholded2, imgThresholded3, getStructuringElement(MORPH_ELLIPSE, Size(4, 4)));
        erode(imgThresholded3, imgThresholded4, getStructuringElement(MORPH_ELLIPSE, Size(4, 4)));

        findContours(imgThresholded4, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

        // Approximate contours to polygons + get bounding rects and circles
        vector<vector<Point> > contours_poly(contours.size());
        vector<Rect> boundRect(contours.size());
        vector<Point2f> center(contours.size());
        vector<float> radius(contours.size());

        for (size_t i = 0; i < contours.size(); i++) {
            approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
            boundRect[i] = boundingRect(Mat(contours_poly[i]));
            //minEnclosingCircle( contours_poly[i], center[i], radius[i] );
        }

        /// Draw polygonal contour + bonding rects + circles
        Mat drawing = Mat::zeros(imgThresholded.size(), CV_8UC3);
        for (size_t i = 0; i < contours.size(); i++) {
            Scalar color = Scalar(255, 255, 255);
            //drawContours( drawing, contours_poly, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point() );
            rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
            //circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
        }

    #ifdef DEBUG
        imshow("Obstacles", drawing); //show the drawn image
        imshow("Original", imgOriginal); //show the original image]
        waitKey(24);
    #endif


    }

    return 0;
}
