cmake_minimum_required(VERSION 2.8.4)
project(lepton)

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_executable(BoundingBoxes BoundingBoxes.cpp)

target_link_libraries( BoundingBoxes ${OpenCV_LIBS} )
