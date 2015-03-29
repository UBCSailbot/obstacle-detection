#include "imu.h"

#define DEBUG_ENABLED

Imu::Imu() {
  USB = open_serial("/dev/ttyUSB0", B115200);
  response = new char[100]();
  imuLog.open ("imuLog.txt");
}

Imu::~Imu() {
  imuLog.close();
}

int Imu::open_serial(const char* port_name, int speed) {
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

char* Imu::readData(char* response) {
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

void Imu::calc(char* response) {
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

void Imu::getData() {
	readData(response);

  time_t now = time(0);
  char* dt = ctime(&now);

  imuLog << dt;
  imuLog << response;
#ifdef DEBUG_ENABLED
  std::cout << dt;
  std::cout << response;
#endif
}
