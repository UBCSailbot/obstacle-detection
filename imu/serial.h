#ifndef SERIAL_H
#define SERIAL_H

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h> 
#include <string>
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

#include <vector>

#define DEFAULT_USB "/dev/ttyUSB0"

int open_serial(const char* port_name, int speed);
char* read_serial(int USB, char* response);
void close_serial(int USB);
void flush_serial(int USB);

#endif