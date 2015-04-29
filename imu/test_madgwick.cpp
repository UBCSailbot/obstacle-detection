#include "MadgwickAHRS.h"
#include "imu_data.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/ext.hpp"
#include "glm/vec3.hpp"

#include <fstream>
#include <sstream>
#include <string>

#include <sys/types.h>
#include <dirent.h>

#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;


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

void videoTest(string imuLogfile, string frameDir) {
	// Populate vector of IMU data instances
	vector<ImuData> dataArray = readImuLogFile(imuLogfile);

	bool firstFrame = true;

	for(int i=0; i<dataArray.size(); i++) {
		ImuData data = dataArray[i];
		// cout << data.toPrettyString(dataArray[i-1].getTimestamp());
		if (firstFrame)
			firstFrame = false;
		else {
			Sensor gyro = data.getGyro();
			Sensor accel = data.getAccel();
			Sensor mag = data.getMag();
			MadgwickAHRSupdate(gyro.x, gyro.y, gyro.z,
							   accel.x, accel.y, accel.z,
							   mag.x, mag.y, mag.z);
			cout << "Quaternion: " << q0 << " " << q1 << " " <<
		 			q2 << " " << " " << q3 << endl;
		 	float qx = *(const_cast<float*>(&q0));
		 	float qy = *(const_cast<float*>(&q1));
		 	float qz = *(const_cast<float*>(&q2));
		 	float qw = *(const_cast<float*>(&q3));
		 	glm::quat q(qx, qy, qz, qw);
		 	glm::vec3 v = glm::eulerAngles(q);
		 	float pitch = v[0] * 180 / M_PI;
		 	float yaw = v[1]* 180 / M_PI;
		 	float roll = v[2]* 180 / M_PI;

		 	// cout << "Euler Angles: pitch=" << pitch << ", roll="
		 	// 	 << roll << ", yaw=" << yaw << endl;
	        
		}
	}
}


int main(int argc, char** argv) {
	
	if (argc < 2) {
		cout << "Usage: "
			 << "test_madgwick <imuLogfile>\n";
		return 1;
	}

	string imuLogfile(argv[1]);
	// string frameDir(argv[2]);
	string frameDir("argv[2]");
	videoTest(imuLogfile, frameDir);
}