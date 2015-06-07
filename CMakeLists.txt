cmake_minimum_required(VERSION 2.8)
project(obstacle_avoidance)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

###########
# SOURCES #
###########

# Add src folders to header search path so that we don't have to `#include` relative paths
include_directories( src/core )
include_directories( src/device )

FILE(GLOB_RECURSE CORE_SOURCE_FILES src/core/*.cpp src/core/*.h)
FILE(GLOB_RECURSE DEVICE_SOURCE_FILES src/device/*.cpp src/device/*.h)

add_executable(rigRunner src/rig/RigRunner.cpp ${CORE_SOURCE_FILES} ${DEVICE_SOURCE_FILES})

#########
# TESTS #
#########

# Add test folders to header search path so that we don't have to `#include` relative paths
include_directories( test/core )
include_directories( test/device )

FILE(GLOB_RECURSE CORE_TEST_FILES test/core/*.cpp test/core/*.h)
FILE(GLOB_RECURSE DEVICE_TEST_FILES test/device/*.cpp test/device/*.h)

# Create target for automated unit tests of histogram functionality
add_executable(runCoreTests test/core/CoreTestRunner.cpp ${CORE_SOURCE_FILES} ${CORE_TEST_FILES})


# IMU testing
add_executable(imuTest
               test/device/imu/IMUTest.cpp
               ${DEVICE_SOURCE_FILES} ${DEVICE_TEST_FILES}
)

# Display testing
add_executable(displayTest
               test/device/display/DisplayTest.cpp
               ${DEVICE_SOURCE_FILES} ${DEVICE_TEST_FILES}
)

# The following command copies the resources folder into the binary directory.
add_custom_command(TARGET runCoreTests POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/resources
                        ${CMAKE_BINARY_DIR}/resources
)

##################
# TEST FRAMEWORK #
##################

# Add google test framework
ADD_SUBDIRECTORY(lib/gtest-1.7.0 gtest)
include_directories(gtest STATIC lib/gtest-1.7.0/include )


#################
# CORE LIBRARIES #
#################

set( CORE_LIBRARIES )

# OpenCV must be independently preinstalled on the host machine
find_package (OpenCV REQUIRED)
list(APPEND CORE_LIBRARIES ${OpenCV_LIBS} )


####################
# DEVICE LIBRARIES #
####################

set( DEVICE_LIBRARIES )

# RTIMULib is compiled with the project
include_directories(RTIMULib STATIC
                    lib/RTIMULib)
ADD_SUBDIRECTORY(lib/RTIMULib RTIMULib)
list(APPEND DEVICE_LIBRARIES RTIMULib)

# Lepton SDK is compiled with the project
include_directories(lib/leptonSDKEmb32PUB)
set(LEPTONSDK_DIR ${CMAKE_SOURCE_DIR}/lib/leptonSDKEmb32PUB)
add_custom_target(
   leptonSDK
   COMMAND make
   WORKING_DIRECTORY ${LEPTONSDK_DIR}
)
add_dependencies(displayTest leptonSDK)
add_dependencies(rigRunner leptonSDK)
add_dependencies(runCoreTests leptonSDK)
list(APPEND DEVICE_LIBRARIES ${LEPTONSDK_DIR}/Debug/libLEPTON_SDK.a)

# rpusbdisp is compiled with the project
set(RPUSBDISP_DIR ${CMAKE_SOURCE_DIR}/lib/rpusbdisp/usermode-sdk)
include_directories(${RPUSBDISP_DIR})
include_directories(${RPUSBDISP_DIR}/infra/include)
include_directories(${RPUSBDISP_DIR}/rpusbdisp-drv/include)
include_directories(${RPUSBDISP_DIR}/deps-wraps/libusbx_wrap/include)
add_custom_target(
   rpusbdisp
   COMMAND ./configure && make
   WORKING_DIRECTORY ${RPUSBDISP_DIR}
)
add_dependencies(rigRunner rpusbdisp)
add_dependencies(displayTest rpusbdisp)
list(APPEND DEVICE_LIBRARIES ${RPUSBDISP_DIR}/build/output/rpusbdisp-drv.a)
list(APPEND DEVICE_LIBRARIES ${RPUSBDISP_DIR}/build/output/librpusbdisp-drv.so)

# # Threads must be independently preinstalled on the host machine
find_package (Threads REQUIRED)
list(APPEND CORE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})


TARGET_LINK_LIBRARIES(rigRunner ${CORE_LIBRARIES} ${DEVICE_LIBRARIES})

TARGET_LINK_LIBRARIES(runCoreTests ${CORE_LIBRARIES} gtest)
TARGET_LINK_LIBRARIES(displayTest ${CORE_LIBRARIES} ${DEVICE_LIBRARIES})
