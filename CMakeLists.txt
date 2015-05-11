cmake_minimum_required(VERSION 3.2)
project(obstacle_avoidance)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(rig_record src/rig/rig_record.cpp src/imu/IMU.cpp src/imu/IMU.h test/moc_IMU.cpp test/moc_IMU.h src/lepton/Lepton.cpp src/lepton/Lepton.h src/lepton/LeptonSPI.cpp src/lepton/LeptonSPI.h src/lepton/LeptonI2C.cpp src/lepton/LeptonI2C.h)

#############
# LIBRARIES #
#############


# Add RTIMULib
include_directories(RTIMULib STATIC
                    lib/RTIMULib)
ADD_SUBDIRECTORY(lib/RTIMULib RTIMULib)
TARGET_LINK_LIBRARIES(rig_record RTIMULib)


# Add Lepton SDK
include_directories(lib/leptonSDKEmb32PUB)
set(LEPTONSDK_DIR ${CMAKE_SOURCE_DIR}/lib/leptonSDKEmb32PUB)
add_custom_target(
   leptonSDK
   COMMAND make
   WORKING_DIRECTORY ${LEPTONSDK_DIR}
)
add_dependencies(rig_record leptonSDK)
target_link_libraries(rig_record ${LEPTONSDK_DIR}/Debug/libLEPTON_SDK.a)


# Add OpenCV
target_link_libraries( rig_record ${OpenCV_LIBS} )


# Add pthreads
find_package (Threads)
target_link_libraries (rig_record ${CMAKE_THREAD_LIBS_INIT})
