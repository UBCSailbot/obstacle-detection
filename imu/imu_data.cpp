#include "imu_data.h"

ImuData::ImuData(float accel_data[3], float gyro_data[3], float mag_data[3]) {
	accel_vector = new float[3];
	gyro_vector = new float[3];
	mag_vector = new float[3];
	for (int i=0; i < 3; i++) {
		accel_vector[i] = accel_data[i];
		gyro_vector[i] = gyro_data[i];
		mag_vector[i] = mag_data[i];
	}	
	raw_init = false; pretty_init = false;
}

ImuData::~ImuData(){
	delete[] accel_vector;
	delete[] gyro_vector;
	delete[] mag_vector;
	if (raw_init)
		delete[] raw_str;
	if (pretty_init)
		delete[] pretty_str;
}

float* ImuData::get_accel() {
	return accel_vector;
}

float* ImuData::get_gyro() {
	return gyro_vector;
}

float* ImuData::get_mag() {
	return mag_vector;
}

char* ImuData::to_raw_str() {
	if (!raw_init) {
		raw_str = new char[127]();
		generate_raw_str(raw_str);
		raw_init = true;
	}
	return raw_str;
}

void ImuData::generate_raw_str(char* s) {
	sprintf(s, "%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
		accel_vector[0], accel_vector[1], accel_vector[2],
		gyro_vector[0], gyro_vector[1], gyro_vector[2],
		mag_vector[0], mag_vector[1], mag_vector[2]);
}

char* ImuData::to_pretty_str() {
	if (!pretty_init) {
		pretty_str = new char[127]();
		generate_pretty_str(pretty_str);
		pretty_init = true;
	}
	return pretty_str;
}

void ImuData::generate_pretty_str(char* s) {
	sprintf(s, "ACCEL: %7.5g %7.5g %7.5g  GYRO: %7.5g %7.5g %7.5g  MAG: %7.5g %7.5g %7.5g\n",
		accel_vector[0], accel_vector[1], accel_vector[2],
		gyro_vector[0], gyro_vector[1], gyro_vector[2],
		mag_vector[0], mag_vector[1], mag_vector[2]);
}