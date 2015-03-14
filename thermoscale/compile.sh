#! /bin/bash
#
# If this call to g++ fails, it may be because your OpenCV libraries are in a different location. In that case try the following command:
#
#     g++ thermoscale.cpp -std=c++11 -o thermoscale $(pkg-config opencv --libs --cflags)
#

echo "Compiling..." && echo

g++ thermoscale.cpp -g -std=c++11 -o thermoscale -I/usr/include/opencv -lopencv_core -lopencv_highgui -lopencv_imgproc

echo "Compilation complete. If there were errors they should be displayed above."
