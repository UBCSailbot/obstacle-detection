#include "Horizon.hpp"
#include "../imu/imu_data.h"
#include "../imu/imu_processor.h"

#include <iostream>
#include <fstream>
#include <string>

#include <sys/types.h>
#include <dirent.h>

#include "opencv2/highgui/highgui.hpp"


using namespace std;
using namespace cv;

void displayHorizonFrame(string fileName, ImuData imuData) {

}

ImuData* readImuLogFile(string fileName) {
	
	ifstream infile(fileName);

}

void smokeTest() {
	// first line of IMU log file
	float accel[] = {23.980814,983.213379,191.846512};
	float gyro[] = {26.547482,-70.787445,21.104984};
	float mag[] = {-178.260864,-586.956543,-214.634140};

	ImuData d(accel, gyro, mag);
	ImuProcessor proc(d);
	Horizon h(proc.getRoll(), proc.getPitch()+ 1.48);

	string imgFile = "/home/paul/sailbot/expt/fluctus/data/02012232moreBoat/tmp_modal100/img_000001.png";

	Mat frame = imread(imgFile);
	line(frame, h.getStart(), h.getEnd(), Scalar(0,0,255), 1);
	cout << "First point: " << h.getStart() << endl;
	cout << "Second point: " << h.getEnd() << endl;
	imshow("Horizon", frame);
	waitKey(0);

}

void videoTest(string imuLogfile, string frameDir) {
	// Populate array of IMU data instances
	ImuData* imuData = readImuLogFile(imuLogfile);

	// Iterate over each frame in frameDir,
	//   and paint a horizon line over it
	DIR *dp;
	struct dirent *ep;     
	dp = opendir (frameDir.c_str());

	int frameCounter = 0;
	if (dp != NULL) {
		while (ep = readdir (dp)) {
			cout << ep->d_name;
			frameCounter ++;
			displayHorizonFrame(string(ep->d_name), imuData[frameCounter]);
		}
		(void) closedir (dp);
	}
	else
		cerr << "Couldn't open directory " << frameDir << endl;
}

int main(int argc, char** argv) {
	
	if (argc < 3) {
		cout << "Usage: "
			 << "test_horizon <imuLogfile> <frameDir>\n";
		return 1;
	}

	string imuLogfile(argv[1]);
	string frameDir(argv[2]);
	// videoTest(imuLogfile, frameDir);

	smokeTest();	
}