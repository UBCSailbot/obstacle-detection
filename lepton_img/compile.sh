gcc -c -o raspberry_pi_capture.o raspberry_pi_capture.c;
g++ -c -o test.o test.cpp;
g++ -o test raspberry_pi_capture.o test.o -I/usr/include/opencv -lopencv_core -lopencv_video -lopencv_highgui;
