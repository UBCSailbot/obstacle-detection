#ifndef IMU_DATA_H
#define IMU_DATA_H

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

typedef std::chrono::time_point<std::chrono::steady_clock> tstamp_t;

class ImuData {
public:
	ImuData(float gyro_data[3], float accel_data[3], 
			float mag_data[3]);
	~ImuData();

	float* get_accel();
	float* get_gyro();
	float* get_mag();
	tstamp_t get_timestamp();

	int millis_since(tstamp_t prev);

	char* to_raw_str(tstamp_t prev_reading);
	char* to_pretty_str(tstamp_t prev_reading);

private:
	float* gyro_vector;
	float* accel_vector;
	float* mag_vector;

	// timestamp is obtained from system clock after successful read.
	tstamp_t timestamp;

	char* raw_str;
	char* pretty_str;

	bool raw_init;
	bool pretty_init;

	void generate_raw_str(char* s, tstamp_t prev_reading);
	void generate_pretty_str(char* s, tstamp_t prev_reading);

};


#endif