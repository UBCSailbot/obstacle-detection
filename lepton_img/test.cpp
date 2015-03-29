extern "C" {
  #include "raspberry_pi_capture.h"
}

#include "test.h"

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {
  printArray(lepton_image, 60, 80);

  capture();
  if(lepton_image)
    std::cout << "after capture" << std::endl;
  
  normalize(lepton_image, 60, 80);
  cv::Mat img(60, 80, CV_8UC1, &(lepton_image[0]));
  imshow("Frame", img);
  cv::waitKey(0);

  printArray(lepton_image, 60, 80);
  
}

void printArray(unsigned int target[][80], int rows, int cols) {
  
  for(int i=0; i<rows; i++) {
    for(int j=0; j<cols; j++) {
      std::cout << target[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void normalize(unsigned int img[][80], int rows, int cols) {

  unsigned int minval = UINT_MAX;
  unsigned int maxval = 0;

  for(int i=0;i<rows;i++) {
	  for(int j=0;j<cols;j++) {

		  if (lepton_image[i][j] > maxval)
			  maxval = lepton_image[i][j];

		  if (lepton_image[i][j] < minval)
			  minval = lepton_image[i][j];

	  }
  }

	for(int i=0;i<rows;i++) {
		for(int j=0;j<cols;j++) {
			img[i][j] = img[i][j] - minval;
		}
	}

}
