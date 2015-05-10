cmake_minimum_required(VERSION 3.2)
project(obstacle_avoidance)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
#add_subdirectory(lepton build)
add_executable(obstacle_avoidance ${SOURCE_FILES} src/imu/IMU.cpp src/imu/IMU.h)
add_executable(rig_record src/rig/rig_record.cpp src/imu/IMU.cpp src/imu/IMU.h test/moc_IMU.cpp test/moc_IMU.h)

include_directories(RTIMULib STATIC
                    lib/RTIMULib)
ADD_SUBDIRECTORY(lib/RTIMULib RTIMULib)

target_link_libraries( rig_record ${OpenCV_LIBS} )
TARGET_LINK_LIBRARIES(rig_record RTIMULib)
find_package (Threads)
target_link_libraries (rig_record ${CMAKE_THREAD_LIBS_INIT})