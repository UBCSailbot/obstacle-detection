cmake_minimum_required(VERSION 3.2)
project(obstacle_avoidance)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

###########
# SOURCES #
###########

set(SOURCE_FILES src/horizon/Horizon.cpp
                 src/lepton/Lepton.cpp
                 src/lepton/LeptonSPI.cpp
                 src/lepton/LeptonI2C.cpp
                 src/imu/IMU.cpp
                 src/imu/ParallelIMU.cpp
                 )
add_executable(rig_record src/rig/RigRunner.cpp ${SOURCE_FILES} test/horizon/HorizonTest.cpp test/horizon/HorizonTest.h)

#########
# TESTS #
#########

set(TEST_FILES ${SOURCE_FILES} test/imu/MockIMU.cpp
                               test/imu/IMUTest.cpp
                               test/horizon/HorizonTest.cpp
                               )
add_executable(runTests test/TestRunner.cpp ${TEST_FILES})


set(LIBRARIES )

#################
# INTERNAL LIBS #
#################

# Add RTIMULib
include_directories(RTIMULib STATIC
                    lib/RTIMULib)
ADD_SUBDIRECTORY(lib/RTIMULib RTIMULib)
list(APPEND LIBRARIES RTIMULib)

# Add Lepton SDK
include_directories(lib/leptonSDKEmb32PUB)
set(LEPTONSDK_DIR ${CMAKE_SOURCE_DIR}/lib/leptonSDKEmb32PUB)
add_custom_target(
   leptonSDK
   COMMAND make
   WORKING_DIRECTORY ${LEPTONSDK_DIR}
)
add_dependencies(rig_record leptonSDK)
list(APPEND LIBRARIES ${LEPTONSDK_DIR}/Debug/libLEPTON_SDK.a)

#################
# EXTERNAL LIBS #
#################

# Add OpenCV
find_package (OpenCV REQUIRED)
list(APPEND LIBRARIES ${OpenCV_LIBS} )


# Add pthreads
find_package (Threads REQUIRED)
list(APPEND LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

TARGET_LINK_LIBRARIES(rig_record ${LIBRARIES})
TARGET_LINK_LIBRARIES(runTests ${LIBRARIES})
