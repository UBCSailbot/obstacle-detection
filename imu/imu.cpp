#include "imu.h"

#define DEBUG_ENABLED

static const std::string ACCEL = "ACCEL";
static const std::string GYRO = "GYRO";
static const std::string MAG = "MAG";

Imu::Imu() {
	USB = open_serial(DEFAULT_USB, B115200);
	response = new char[100]();
}

Imu::~Imu() {
	close_serial(USB);
}

/**
 * Read a line from the serial port and split it
 *  at every instance of a tab character.
 */
void Imu::read_str(std::string dst[4]) {
	read_serial(USB, response);
	//read_serial(USB, response);

	std::stringstream ss(response);
	std::string item;
	const char delim = '\t';

	for (int i=0; i < 4; i++) {
		std::getline(ss, item, delim);
		dst[i] = item;
	}
}

/**
 * Read the given field from IMU.
 * Attempts to get values for the given field until a certain maximum
 *	 number of attempts.
 * The number of attempts indicates the number of lines read from the IMU.
 * Keep in mind that the device outputs accel/gyro data on alternating lines.
 * Thus, the number of attempts for one particular field is really half the
 * number of total line reads. 
 *
 * Returns true if read is successful, false otherwise.
 */
bool Imu::get_field(std::string field_name, float vals[3], 
		int max_reads) {

	int num_reads = 0;
	std::string* string_response = new std::string[4]();
	bool success = false;

	for (int i=0; i < max_reads; i++) {
		read_str(string_response);
        num_reads ++;

        if (string_response[0].find(field_name) != 
        		std::string::npos) {
        	vals[0] = std::stof(string_response[1]);
        	vals[1] = std::stof(string_response[2]);
        	vals[2] = std::stof(string_response[3]);
        	success = true;
        	break;
        }
	}
	
	delete[] string_response;
	return success;
}

ImuData Imu::getData() {
	float* accel_data = new float[3];
	float* gyro_data = new float[3];
	float* mag_data = new float[3];

	bool success = true;
	success &= get_field(ACCEL, accel_data);
	success &= get_field(GYRO, gyro_data);
	success &= get_field(MAG, mag_data);

	if (!success) {
		std::cout << "Failed to get data\n";
	}

	return ImuData(accel_data, gyro_data, mag_data);
}
