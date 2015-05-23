cmake_minimum_required(VERSION 2.8.4)
project( 16to8 )

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

add_executable( 16to8 16to8.cpp)

target_link_libraries( 16to8 ${OpenCV_LIBS} )
