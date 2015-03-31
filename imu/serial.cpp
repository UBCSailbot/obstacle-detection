#include "serial.h"

// Borrowed from:
// http://stackoverflow.com/questions/18108932/linux-c-serial-port-reading-writing

int open_serial(const char* port_name, int speed) {
	int USB = open( port_name, O_RDONLY| O_NOCTTY );
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

char* read_serial(int USB, char* response) {
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

void close_serial(int USB) {
	close(USB);
}
