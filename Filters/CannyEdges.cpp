#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;


/** @function main */
int main( int argc, char** argv )
{
	 Mat frame, detected_edges, dst, frame_gray, crop;


	  int buoy_start = 132000; //2.2 mins
	  int lowThreshold = 65;
	  int ratio = 3;
	  int kernel_size = 3;




  String path = "/home/josh/SailbotOpenCV/data/buoy.avi";
  VideoCapture cap(path); // open the video file for reading

  if ( !cap.isOpened() )  // if not success, exit program
     {
          std::cout << "Cannot open the video file" << std::endl;
          return -1;
     }

  cap.set(CV_CAP_PROP_POS_MSEC, buoy_start); //start the video at 2.5 mins

  double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video

  namedWindow("Original",CV_WINDOW_NORMAL); //create a window for the original video
  namedWindow("Edges", CV_WINDOW_NORMAL); //create a window for the sharpened
  int X = 0;
  int Y = 20;
  int Width = 50;
  int Height = 60;

  while(1)
     {
         bool bSuccess = cap.read(frame); // read a new frame from video
         crop  = frame(Rect(X,Y,Width,Height)).clone();
         frame = frame(Rect(X,Y,Width,Height));

         cvtColor( crop, frame_gray, CV_BGR2GRAY );

         dst.create( crop.size(), crop.type() );

         blur( frame_gray, detected_edges, Size(3,3) );

           /// Canny detector
         Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );


           /// Using Canny's output as a mask, we display our result
           dst = Scalar::all(0);

           crop.copyTo( dst, detected_edges);


          if (!bSuccess) //if not success, break loop
         {
        	  	  	  	std::cout << "Cannot read frame from video file" << std::endl;
                        break;
         }

         imshow("Original", frame); //show the frame in "MyVideo" window
         imshow( "Edges", dst );

         if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
        {
        	 	 std::cout << "esc key pressed by user" << std::endl;
                 break;
        }
     }

     return 0;
  }
