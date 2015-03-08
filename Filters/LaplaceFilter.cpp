#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;



/** @function main */
int main( int argc, char** argv )
{
	 Mat src, src_gray, dst, frame, abs_dst;
	  int kernel_size = 3;
	  int scale = 1;
	  int delta = 0;
	  int ddepth = CV_16S;


  String path = "/home/josh/SailbotOpenCV/data/sunsparkles.avi";
  VideoCapture cap(path); // open the video file for reading

  if ( !cap.isOpened() )  // if not success, exit program
     {
          std::cout << "Cannot open the video file" << std::endl;
          return -1;
     }

  double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video

  namedWindow("Original",CV_WINDOW_NORMAL); //create a window for the original video
  namedWindow("Laplace", CV_WINDOW_NORMAL); //create a window for the sharpened

  while(1)
     {
         bool bSuccess = cap.read(frame); // read a new frame from video
         GaussianBlur( frame, src, Size(3,3), 0, 0, BORDER_DEFAULT );
         Laplacian( src, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
         convertScaleAbs( dst, abs_dst );


          if (!bSuccess) //if not success, break loop
         {
        	  	  	  	std::cout << "Cannot read frame from video file" << std::endl;
                        break;
         }

         imshow("Original", frame); //show the frame in "MyVideo" window
         imshow( "Laplace", abs_dst );

         if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
        {
        	 	 std::cout << "esc key pressed by user" << std::endl;
                 break;
        }
     }

     return 0;
  }
