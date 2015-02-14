cmake_minimum_required(VERSION 2.8.4)
project(lepton)

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Lepton.cpp)

add_executable(lepton ${SOURCE_FILES})

target_link_libraries( lepton ${OpenCV_LIBS} )