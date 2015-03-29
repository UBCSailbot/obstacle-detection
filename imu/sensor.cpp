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

#define DEBUG_ENABLED

int open_serial(const char* port_name, int speed) {
	int USB = open( port_name, O_RDWR| O_NOCTTY );

	struct termios tty;
	struct termios tty_old;
	memset (&tty, 0, sizeof tty);

	/* Error Handling */
	if ( tcgetattr ( USB, &tty ) != 0 ) {
	   std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
	}

	/* Save old tty parameters */
	tty_old = tty;

	/* Set Baud Rate */
	cfsetospeed (&tty, speed);
	cfsetispeed (&tty, speed);

	/* Setting other Port Stuff */
	tty.c_cflag     &=  ~PARENB;            // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;

	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_cc[VMIN]   =  1;                  // read doesn't block
	tty.c_cc[VTIME]  =  1;                  // 0.5 seconds read timeout
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	/* Make raw */
	cfmakeraw(&tty);

	/* Flush Port, then applies attributes */
	tcflush( USB, TCIFLUSH );
	if ( tcsetattr ( USB, TCSANOW, &tty ) != 0) {
	   std::cout << "Error " << errno << " from tcsetattr" << std::endl;
	}

	return USB;
}

char* read(int USB, char* response) {
	int n = 0, 
	    spot = 0;
	char buf = '\0';

	do {
	   n = read( USB, &buf, 1 );
	   sprintf( &response[spot], "%c", buf );
	   spot += n;
	} while( buf != '\r' && n > 0);

	if (n < 0) {
	   std::cout << "Error reading: " << strerror(errno) << std::endl;
	}
	else if (n == 0) {
	    std::cout << "Read nothing!" << std::endl;
	}
	else {
	}

	return response;
}

void calc(char* response) {
  std::vector<std::string> elems;
  std::stringstream ss(response);
  std::string item;
  const char delim = '\t';

  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
#ifdef DEBUG_ENABLED
  std::cout << elems[0] << std::endl;
  std::cout << elems[1] << std::endl;
  std::cout << elems[2] << std::endl;
  std::cout << elems[3] << std::endl;
#endif
}

int main() {
    int USB = open_serial("/dev/ttyUSB0", B115200);
    char* response = new char[100]();
    std::ofstream imuLog;
    imuLog.open ("imuLog.txt");

    for(int i=0; i < 135; i++) {
	    read(USB, response);
	    // std::string str = std::string(response);
	    // std::cout << "Read " + str.size() << " bytes" << std::endl;
      calc(response);
#ifdef DEBUG_ENABLED
      std::cout << response;
#endif
      imuLog << response;
    }
    imuLog.close();
}
