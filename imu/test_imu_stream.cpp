#include "imu_processor.h"
#include "imu_data.h"
#include "imu.h"
#include <iostream>

using namespace std;

int main() {
	Imu imu;
	ImuProcessor processor;

	float dummy[3] = {0};
	ImuData data(dummy, dummy, dummy);
	processor.update(data);

	cout << "Starting Capture" << endl;

	while (1) {
		data = imu.getData();
		processor.update(data);
		sleep(1);
		cout << "Roll: " << processor.getRoll();
		cout << "  Pitch: " << processor.getPitch();
		cout << endl;

	}
}