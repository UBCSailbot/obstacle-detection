#include "Horizon.hpp"
#include "../imu/imu_data.h"
#include "../imu/imu_processor.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <sys/types.h>
#include <dirent.h>

#include "opencv2/highgui/highgui.hpp"

//#define PITCH_OFFSET -3.9
#define PITCH_OFFSET -1.67

using namespace std;
using namespace cv;

void displayHorizonFrame(string fileName, Horizon h) {
	Mat frame = imread(fileName);
	line(frame, h.getStart(), h.getEnd(), Scalar(0,0,255), 1);
	cout << "First point: " << h.getStart() << endl;
	cout << "Second point: " << h.getEnd() << endl;
	imshow("Horizon", frame);
	char c = waitKey(30);
	if (c == 'p') {
		waitKey(0);
	}
}

void fill3array(istringstream& stream, float array[], char delim) {
	string token;
	for (int i= 0; i < 3; i++) {
		getline(stream, token, delim);
		array[i] = stof(token);
	}
}

vector<ImuData> readImuLogFile(string fileName) {

	vector<ImuData> dataArray;
	ifstream infile(fileName);

	string line, token;
	char delim = ',';
	TimePoint timeOfPrevReading;
	bool firstReading = true;

	while (getline(infile, line)) {
		istringstream lineStream(line);
	    
	    // first, get timestep in milliseconds
	    getline(lineStream, token, ':');
	    int timeStepMillis = stoi(token);

	    // then parse each of the IMU data fields
	    float accel[3];
	    float gyro[3];
	    float mag[3];
	    fill3array(lineStream, accel, delim);
	    fill3array(lineStream, gyro, delim);
	    fill3array(lineStream, mag, delim);

	    ImuData currentData(accel, gyro, mag);
	    if (firstReading) {
	    	timeOfPrevReading = currentData.getTimestamp();
	    	firstReading = false;
	    }
	    else {
	    	TimePoint adjustedTimePoint = timeOfPrevReading + 
	    		chrono::milliseconds(timeStepMillis);
	    	currentData.setTimestamp(adjustedTimePoint);
	    	timeOfPrevReading = adjustedTimePoint;
	    }

	    dataArray.push_back(currentData);
	}

	return dataArray;

}

bool startsWith (string const &fullString, string const &start) {
    if (fullString.length() >= start.length()) {
        return (0 == fullString.compare (0, start.length(), start));
    } else {
        return false;
    }
}

bool endsWith (string const &fullString, string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

bool validFrameFile(string fileName) {
	return startsWith(fileName, "img_") && endsWith(fileName, ".png");
}

void videoTest(string imuLogfile, string frameDir) {
	// Populate vector of IMU data instances
	vector<ImuData> dataArray = readImuLogFile(imuLogfile);
	ImuProcessor proc(dataArray[0]);

	// for (int i=1; i< dataArray.size(); i++) {
	// 	ImuData* prev = &(dataArray[i-1]);
	// 	cout << dataArray[i].toPrettyString(dataArray[i-1].getTimestamp());
	// }

	// Iterate over each frame in frameDir,
	//   and paint a horizon line over it
	DIR *dp;
	struct dirent *ep;     
	dp = opendir (frameDir.c_str());
	bool firstFrame = true;

	int frameCounter = 0;
	if (dp != NULL) {
		while (ep = readdir (dp)) {
			string fileName(ep->d_name);
			if (!validFrameFile(fileName))
				continue;
			frameCounter ++;
			cout << dataArray[frameCounter].toPrettyString(dataArray[frameCounter-1].getTimestamp());
			if (firstFrame)
				firstFrame = false;
			else
				proc.update(dataArray[frameCounter]);
				if (frameCounter % 270 == 0) {
					proc.resetGyro(dataArray[frameCounter]);
					cout << "RESETTING" << endl;
					waitKey(0);
				}
			Horizon h(proc.getRoll(), proc.getPitch() + PITCH_OFFSET);
			displayHorizonFrame(frameDir + "/" + fileName, h);
		}
		(void) closedir (dp);
	}
	else
		cerr << "Couldn't open directory " << frameDir << endl;
}


void smokeTest() {
	// first line of IMU log file
	float accel[] = {23.980814,983.213379,191.846512};
	float gyro[] = {26.547482,-70.787445,21.104984};
	float mag[] = {-178.260864,-586.956543,-214.634140};

	ImuData d(accel, gyro, mag);
	ImuProcessor proc(d);
	Horizon h(proc.getRoll(), proc.getPitch() + PITCH_OFFSET);

	string imgFile = "/home/paul/sailbot/expt/fluctus/data/02012232moreBoat/tmp_modal100/img_000001.png";

	Mat frame = imread(imgFile);
	line(frame, h.getStart(), h.getEnd(), Scalar(0,0,255), 1);
	cout << "First point: " << h.getStart() << endl;
	cout << "Second point: " << h.getEnd() << endl;
	imshow("Horizon", frame);
	waitKey(0);

}

int main(int argc, char** argv) {
	
	if (argc < 3) {
		cout << "Usage: "
			 << "test_horizon <imuLogfile> <frameDir>\n";
		return 1;
	}

	string imuLogfile(argv[1]);
	string frameDir(argv[2]);
	videoTest(imuLogfile, frameDir);

	// smokeTest();	
}