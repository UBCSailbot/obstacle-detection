cmake_minimum_required(VERSION 2.8.4)
project(rig_record)



find_package( OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(SOURCE_FILES
    ../lepton_video/Lepton.cpp
    ../lepton_video/SPI.cpp
    ../imu/imu.cpp
    ../imu/serial.cpp
    ../imu/imu_data.cpp
    )

add_executable(rig_record rig_record.cpp ${SOURCE_FILES})

target_link_libraries( rig_record ${OpenCV_LIBS} )
