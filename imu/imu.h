#ifndef IMU
#define IMU

#include <stdio.h>
#include <sstream>
#include <ctime>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h> 
#include <string>
#include <vector>
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

class Imu {
public:

  Imu();
  ~Imu();

  void getData();

private:
  int USB;
  char* response;
  std::ofstream imuLog;

  char* readData(char* response);
  int open_serial(const char* port_name, int speed);
  void calc(char* response);

};

#endif
