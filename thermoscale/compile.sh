#! /bin/bash
#
# If this call to g++ fails, it may be because your OpenCV libraries are in a different location. In that case try the following command:
#
#     g++ thermoscale.cpp -std=c++11 -o thermoscale $(pkg-config opencv --libs --cflags)
#

echo "Compiling..." && echo

g++ -c thermoscale.cpp -std=c++11 -g
g++ -c SelectedPoints.cpp -std=c++11 -g
g++ -o thermoscale thermoscale.o SelectedPoints.o -g -I/usr/include/opencv -lopencv_core -lopencv_highgui -lopencv_imgproc

echo "Compilation complete. If there were errors they should be displayed above."
