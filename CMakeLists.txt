cmake_minimum_required(VERSION 2.8)
project(obstacle_avoidance)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

###########
# SOURCES #
###########

set(SOURCE_FILES src/display/RoboPeakUSBDisplay.cpp
                 src/display/DesktopDisplay.cpp
                 src/horizon/Horizon.cpp
                 src/imageProc/SimpleRescaler.cpp
                 src/imageProc/ModalRescaler.cpp
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

set(TEST_FILES ${SOURCE_FILES} test/imu/MockIMU.cpp
                               test/imu/IMUTest.cpp
                               test/horizon/HorizonTest.cpp
                               )

add_executable(runTests test/TestRunner.cpp ${TEST_FILES})
add_executable(displayTest test/display/DisplayTest.cpp ${TEST_FILES})

###########
# WINDOWS #
###########

set(WIN_SOURCE_FILES    src/horizon/Horizon.cpp)
set(WIN_TEST_FILES ${WIN_SOURCE_FILES} test/horizon/HorizonTest.cpp)

add_executable(winRunTests test/WinTestRunner.cpp ${WIN_TEST_FILES})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

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
find_package (OpenCV REQUIRED)
list(APPEND LIBRARIES ${OpenCV_LIBS} )

# Add pthreads
find_package (Threads REQUIRED)
list(APPEND LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

TARGET_LINK_LIBRARIES(rigRunner ${LIBRARIES})
TARGET_LINK_LIBRARIES(runTests ${LIBRARIES})
TARGET_LINK_LIBRARIES(displayTest ${LIBRARIES})
TARGET_LINK_LIBRARIES(winRunTests ${OpenCV_LIBS})

