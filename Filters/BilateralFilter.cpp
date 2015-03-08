#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;



/** @function main */
int main( int argc, char** argv )
{
	 Mat src, frame;
	 int sunsparkles_start = 135000; //2.5 mins
	 int buoy_start = 132000; //2.2 mins


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
  namedWindow("Bilateral Filter", CV_WINDOW_NORMAL); //create a window for the sharpened

  while(1)
     {
         bool bSuccess = cap.read(frame); // read a new frame from video
         bilateralFilter(frame, src ,9,60,75);


          if (!bSuccess) //if not success, break loop
         {
        	  	  	  	std::cout << "Cannot read frame from video file" << std::endl;
                        break;
         }

         imshow("Original", frame); //show the frame in "MyVideo" window
         imshow( "Bilateral Filter", src );

         if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
        {
        	 	 std::cout << "esc key pressed by user" << std::endl;
                 break;
        }
     }

     return 0;
  }
