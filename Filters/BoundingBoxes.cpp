#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {

    int buoy_start = 132000; //2.2 mins
    String path = "betterbouy.mov";
    VideoCapture cap(path); //capture the video from web cam

    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "Cannot open the video" << endl;
        return -1;
    }

//    cap.set(CV_CAP_PROP_POS_MSEC, buoy_start); //start the video at 2.5 mins
    namedWindow("Control", CV_WINDOW_NORMAL);
    namedWindow("Obstacles", CV_WINDOW_NORMAL);
//    namedWindow("Threshold", CV_WINDOW_NORMAL);
//    namedWindow("Threshold1", CV_WINDOW_NORMAL);
//    namedWindow("Threshold2", CV_WINDOW_NORMAL);
//    namedWindow("Threshold3", CV_WINDOW_NORMAL);
//    namedWindow("Threshold4", CV_WINDOW_NORMAL);
    namedWindow("Original", CV_WINDOW_NORMAL);

    moveWindow("Obstacles", 0, 0);
    resizeWindow("Obstacles", 500, 500);
//    moveWindow("Threshold", 0, 580);
//    resizeWindow("Threshold", 500, 500);
//    moveWindow("Threshold1", 0, 1060);
//    resizeWindow("Threshold1", 500, 500);
//    moveWindow("Threshold2", 1000, 580);
//    resizeWindow("Threshold2", 500, 500);
//    moveWindow("Threshold3", 580, 0);
//    resizeWindow("Threshold3", 500, 500);
//    moveWindow("Threshold4", 580, 580);
//    resizeWindow("Threshold4", 500, 500);
    moveWindow("Original", 580, 1640);
    resizeWindow("Original", 500, 500);


    int iLowH = 0;
    int iHighH = 179;

    int iLowS = 0;
    int iHighS = 255;

    int iLowV = 110;
    int iHighV = 255;

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


    int frame_counter = 1;
    char file_name[50];
    string output_folder = "output";


    while (true) {
        Mat imgOriginal, imgLap;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video
        // imgOriginal  = imgOriginal(Rect(X,Y,Width,Height)).clone(); // Cut away horizon


        if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        Mat imgHSV;

        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

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
//        imshow("Threshold", imgThresholded); //show the thresholded image
//        imshow("Threshold1", imgThresholded1); //show the thresholded image
//        imshow("Threshold2", imgThresholded2); //show the thresholded image
//        imshow("Threshold3", imgThresholded3); //show the thresholded image
//        imshow("Threshold4", imgThresholded4); //show the thresholded image
        imshow("Obstacles", drawing); //show the drawn image
        imshow("Original", imgOriginal); //show the original image]

        sprintf(file_name, "img_%06d.png", frame_counter);
        cv::imwrite(output_folder + "/" + file_name, drawing); // save the current frame as a .png file
        frame_counter++;

        if (waitKey(30) == 27) { //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
            cout << "esc key is pressed by user" << endl;
            break;
        }
    }

    return 0;

}
