#include "imu_data.h"
#include "imu_processor.h"
#include <iostream>
#include <unistd.h>

using namespace std;

void output(ImuProcessor processor) {
	// output pitch & roll with getPitch & getRoll
	cout << "Roll: " << processor.getRoll() << endl;
	cout << "Pitch: " << processor.getPitch() << endl;
}

void testResetGyro() {
	//
}

int main() {
	float accel[] = {-996, 0, -996};
	float gyro[] = {0, 0, 0};
	float mag[] = {0,0,0};
	ImuData data(accel, gyro, mag);
	ImuProcessor processor;
	processor.update(data);

	sleep(2);
	float gyro2[] = {2, 0, 0};
	ImuData data2(accel, gyro2, mag);
	processor.update(data2);
	
	output(processor);
	// read IMUdata from file

	sleep(1);
	float gyro3[] = {1, 1, 0};
	ImuData data3(accel, gyro3, mag);
	processor.update(data3);
	output(processor);

	processor.resetGyro();
	output(processor);




}
