#ifndef IMU_H
#define IMU_H

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string.h> 
#include <string>
#include <vector>
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions
#include <stdexcept>

#include "imu_data.h"
#include "serial.h"

class Imu {
public:

	Imu();
	~Imu();

	ImuData getData();

private:
	int USB;
	char* response;

	void read_str(std::string dst[4]);
	bool get_field(std::string field_name, float vals[3], 
		int max_reads=10);

};

#endif
