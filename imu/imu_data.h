#ifndef IMU_DATA_H
#define IMU_DATA_H

#include <iostream>
#include <iomanip>
#include <string>

class ImuData {
public:
	ImuData(float gyro_data[3], float accel_data[3], float mag_data[3]);
	~ImuData();

	float* get_accel();
	float* get_gyro();
	float* get_mag();
	char* to_raw_str();
	char* to_pretty_str();

private:
	float* gyro_vector;
	float* accel_vector;
	float* mag_vector;
	char* raw_str;
	char* pretty_str;

	bool raw_init;
	bool pretty_init;

	void generate_raw_str(char* s);
	void generate_pretty_str(char* s);
};


#endif