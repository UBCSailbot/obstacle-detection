
#include "Lepton.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

#define APP_NAME "Lepton Capture"
#define WIN_ZOOM_FACTOR 8
#define WIN_WIDTH 80 * WIN_ZOOM_FACTOR
#define WIN_HEIGHT 60 * WIN_ZOOM_FACTOR

int main() {
    Lepton lepton;
    cout << "Starting Capture" << endl;

    bool trackingEnabled = false;
    bool debugModeEnabled = false;
    Mat frame(60, 80, CV_16UC1);
    Mat eightBit(60, 80, CV_8UC1);
    Mat displayed(WIN_HEIGHT, WIN_WIDTH, CV_8UC1);
    Mat output(60, 80, CV_8UC1);

    int iLowH = 0;
    int iHighH = 179;

    int iLowS = 0;
    int iHighS = 255;

    int iLowV = 0;
    int iHighV = 255;
    
    RNG rng(12345);
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    //Create trackbars in "Control" window
    cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    cvCreateTrackbar("HighH", "Control", &iHighH, 179);

    cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);

    cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);

    /* Cut away above horizon boundaries */
    int X = 0;
    int Y = 20;
    int Width = 55;
    int Height = 60;

    while (1) {

        lepton.GetFrame(frame, eightBit);

        Mat displayed(WIN_HEIGHT, WIN_WIDTH, CV_8UC1);
//        resize(eightBit, displayed, displayed.size(), 0, 0, INTER_NEAREST);

        if (trackingEnabled) {
            GaussianBlur(eightBit, output, Size(3, 3), 0, 0, BORDER_DEFAULT);
            Laplacian(output, output, CV_16S, 3, 1, 0, BORDER_DEFAULT);
            convertScaleAbs(output, output);

            imshow("Filtered", output);
        }

//        imshow(APP_NAME, displayed);
        imshow(APP_NAME, eightBit);

        Mat imgHSV;

        cvtColor(eightBit, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

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
        imshow("Threshold", imgThresholded); //show the thresholded image
        imshow("Threshold1", imgThresholded1); //show the thresholded image
        imshow("Threshold2", imgThresholded2); //show the thresholded image
        imshow("Threshold3", imgThresholded3); //show the thresholded image
        imshow("Threshold4", imgThresholded4); //show the thresholded image
        imshow("Obstacles", drawing); //show the thresholded image

        // Check to see if a button has been pressed.
        // this 10ms delay is necessary for proper operation of this program
        // if removed, frames will not have enough time to refresh and a blank
        // image will appear.
        switch (waitKey(30)) {
            case 113:
            case 27: //'esc' or 'q' key has been pressed, exit program.
                return 0;
            case 116: //'t' has been pressed. this will toggle tracking
                trackingEnabled = !trackingEnabled;
                cout << (!debugModeEnabled ? "Tracking disabled." : "Tracking enabled.") << endl;
                break;
            case 100: //'d' has been pressed. this will debug mode
                debugModeEnabled = !debugModeEnabled;
                cout << (!debugModeEnabled ? "Debug mode disabled." : "Debug mode enabled.") << endl;
                break;
            case 112: //'p' has been pressed. this will pause/resume the code.
                cout << "Code paused, press 'p' again to resume" << endl;
                while (true) {
                    if (waitKey() == 112) {
                        cout << "Code Resumed" << endl;
                        break;
                    }
                }

            default:
                break;
        }
    }
}
