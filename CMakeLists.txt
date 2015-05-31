cmake_minimum_required(VERSION 2.8)
project(obstacle_avoidance)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

###########
# SOURCES #
###########

# Add src folder to header search path so that we don't have to `#include` relative paths
include_directories( src )

set(SOURCE_FILES src/display/DesktopDisplay.cpp
                 src/display/Display.h
                 src/display/RoboPeakUSBDisplay.cpp
                 src/geometry/Horizon.cpp
                 src/geometry/Line.cpp
                 src/imageProc/EightBitWindowRescaler.cpp
                 src/imageProc/core/HorizonImageHistogram.cpp
                 src/imageProc/core/ImageHistogram.cpp
                 src/imageProc/SimpleRescaler.cpp
                 src/imageProc/HorizonModalRescaler.cpp
                 src/imageProc/HorizonRescaler.h
                 src/imageProc/ModalRescaler.cpp
                 src/imageProc/Rescaler.h
                 src/imageTypes/Image8bit.cpp
                 src/imageTypes/Image16bit.cpp
                 src/lepton/Lepton.cpp
                 src/lepton/LeptonSPI.cpp
                 src/lepton/LeptonI2C.cpp
                 src/imu/IMU.cpp
                 src/imu/ParallelIMU.cpp
                 )


add_executable(rigRunner src/rig/RigRunner.cpp ${SOURCE_FILES})

#########
# TESTS #
#########

# Add test folder to header search path so that we don't have to `#include` relative paths
include_directories( test )

set(TEST_FILES ${SOURCE_FILES} test/imageProc/core/HorizonImageHistogramTest.cpp
                               test/imu/MockIMU.cpp
                               test/imu/IMUTest.cpp
                               test/geometry/HorizonTest.cpp
                               )

add_executable(runTests test/TestRunner.cpp ${TEST_FILES})
add_executable(displayTest test/display/DisplayTest.cpp ${TEST_FILES})
add_executable(imageDisplayDriver test/ImageDisplayDriver.cpp ${TEST_FILES})

##################
# TEST FRAMEWORK #
##################

# Add google test framework
ADD_SUBDIRECTORY(lib/gtest-1.7.0 gtest)
include_directories(gtest STATIC lib/gtest-1.7.0/include )

###########
# WINDOWS #
###########

set(WIN_SOURCE_FILES    src/geometry/Horizon.cpp)
set(WIN_TEST_FILES ${WIN_SOURCE_FILES} test/geometry/HorizonTest.cpp
                                       test/sunImage/SunImageTest.cpp
)

add_executable(winRunTests test/WinTestRunner.cpp ${WIN_TEST_FILES})
# Please also see the lines appended to the section of this file
#  that attempts to load the OpenCV installation.

#################
# INTERNAL LIBS #
#################

set(LIBRARIES )

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
add_dependencies(displayTest leptonSDK)
add_dependencies(rigRunner leptonSDK)
add_dependencies(runTests leptonSDK)
list(APPEND LIBRARIES ${LEPTONSDK_DIR}/Debug/libLEPTON_SDK.a)

# Add rpusbdisp
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
list(APPEND LIBRARIES ${RPUSBDISP_DIR}/build/output/rpusbdisp-drv.a)
list(APPEND LIBRARIES ${RPUSBDISP_DIR}/build/output/librpusbdisp-drv.so)

#################
# EXTERNAL LIBS #
#################

# Add OpenCV
if( CYGWIN )
    # TODO: This is a dirty hack meant to add OpenCV on Windows systems, that only works on Derek's machine.
    set(OpenCV_DIR /home/DerekLun/build_shared_release)
endif( CYGWIN )
find_package (OpenCV)
list(APPEND LIBRARIES ${OpenCV_LIBS} )

# Add pthreads
find_package (Threads REQUIRED)
list(APPEND LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

TARGET_LINK_LIBRARIES(rigRunner ${LIBRARIES})
TARGET_LINK_LIBRARIES(runTests ${LIBRARIES} gtest)
TARGET_LINK_LIBRARIES(displayTest ${LIBRARIES})
TARGET_LINK_LIBRARIES(winRunTests ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(imageDisplayDriver ${LIBRARIES} gtest)

