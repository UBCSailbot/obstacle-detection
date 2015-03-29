cmake_minimum_required(VERSION 2.8.4)
project(lepton)

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES
    Lepton.h
    Lepton.cpp
    SPI.h
    SPI.cpp
   	)

add_executable(lepton main.cpp ${SOURCE_FILES})

target_link_libraries( lepton ${OpenCV_LIBS} )
