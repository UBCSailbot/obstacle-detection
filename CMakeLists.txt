cmake_minimum_required(VERSION 2.8)
project(obstacle_detection)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

############
# INCLUDES #
############

# include core libraries
include(lib/core_libs.cmake)

# include device libraries
include(lib/device_libs.cmake)

# include test framework
include(lib/test_libs.cmake)

# include source files
include(src/src.cmake)

# include test files
include(test/test.cmake)

# defines the target `migrateResources`, used in tests
include(resources/res.cmake)

set( DEVICE_LIBS )

# RTIMULib is compiled with the project
include_directories(RTIMULib STATIC
lib/RTIMULib/RTIMULib)
add_subdirectory(lib/RTIMULib/RTIMULib RTIMULib)
list(APPEND DEVICE_LIBS RTIMULib)


# Lepton SDK is compiled with the project
include_directories(${CMAKE_SOURCE_DIR}/lib/LeptonModule/software/raspberrypi_libs/leptonSDKEmb32PUB)
set(LEPTONSDK_DIR ${CMAKE_SOURCE_DIR}/lib/LeptonModule/software/raspberrypi_libs/leptonSDKEmb32PUB)
add_custom_command(
<<<<<<< HEAD
<<<<<<< HEAD
   OUTPUT ${LEPTONSDK_DIR}/Debug
   COMMAND make
   WORKING_DIRECTORY ${LEPTONSDK_DIR}
 )
add_custom_target(leptonSDK DEPENDS ${LEPTONSDK_DIR}/Debug)
=======
   OUTPUT ${LEPTONSDK_DIR}/Debug
   COMMAND make
   WORKING_DIRECTORY ${LEPTONSDK_DIR}
 )
add_custom_target(leptonSDK DEPENDS ${LEPTONSDK_DIR}/Debug)
>>>>>>> 2f73e4b... made cmake work on clone


list(APPEND DEVICE_LIBS ${LEPTONSDK_DIR}/Debug/libLEPTON_SDK.a)


# dlib is complied with the  project
include(${CMAKE_SOURCE_DIR}/lib/dlib/dlib/cmake)



# rpusbdisp is compiled with the project
set(RPUSBDISP_DIR ${CMAKE_SOURCE_DIR}/lib/rpusbdisp/usermode-sdk)
include_directories(${RPUSBDISP_DIR})
include_directories(${RPUSBDISP_DIR}/infra/include)
include_directories(${RPUSBDISP_DIR}/rpusbdisp-drv/include)
include_directories(${RPUSBDISP_DIR}/deps-wraps/libusbx_wrap/include)
if(NOT EXISTS ${RPUSBDISP_DIR}/Makefile OR NOT EXISTS ${RPUSBDISP_DIR}/Makefile.conf)
    execute_process(COMMAND ./configure
                    WORKING_DIRECTORY ${RPUSBDISP_DIR}
    )
endif(NOT EXISTS ${RPUSBDISP_DIR}/Makefile OR NOT EXISTS ${RPUSBDISP_DIR}/Makefile.conf)
add_custom_target(
   rpusbdisp
   COMMAND make
   WORKING_DIRECTORY ${RPUSBDISP_DIR}
)

list(APPEND DEVICE_LIBS ${RPUSBDISP_DIR}/build/output/rpusbdisp-drv.a)
list(APPEND DEVICE_LIBS ${RPUSBDISP_DIR}/build/output/librpusbdisp-drv.so)


# Threads library must be independently preinstalled on the host machine
find_package (Threads REQUIRED)
list(APPEND CORE_LIBS ${CMAKE_THREAD_LIBS_INIT})


###########
# SOURCES #
###########

# Add src folders to header search path so that we don't have to `#include` relative paths
include_directories( src/core )
include_directories( src/device )

file(GLOB_RECURSE CORE_SOURCE_FILES src/core/*.cpp src/core/*.h)
file(GLOB_RECURSE DEVICE_SOURCE_FILES src/device/*.cpp src/device/*.h)

# Add targets for separately compiling source files
add_library(src_core OBJECT ${CORE_SOURCE_FILES})
add_library(obstdetect_core STATIC $<TARGET_OBJECTS:src_core>)
add_library(obstdetect_full STATIC $<TARGET_OBJECTS:src_core> ${DEVICE_SOURCE_FILES})
=======
###############
# EXECUTABLES #
###############
>>>>>>> 0b8e678... massive cleanup in CMakeLists.txt

add_executable(liveFeeder src/main/LiveFeed.cpp)
target_link_libraries(liveFeeder obstdetect_full)

add_executable(rigRunner src/main/RigRunner.cpp)
target_link_libraries(rigRunner obstdetect_full)

add_executable(rescale src/main/RunRescaling.cpp)
target_link_libraries(rescale obstdetect_core)

add_executable(sunImageRunner src/main/SunImageRunner.cpp)
target_link_libraries(sunImageRunner obstdetect_core)

add_executable(objectDetectionRunner src/main/ObjectDetectionRunner.cpp)
target_link_libraries(objectDetectionRunner dlib)

add_executable(objectDetectionTrainer src/main/ObjectDetectionTrainer.cpp)
add_executable(objectDetectionModelGenerator src/main/ObjectDetectionModelGenerator.cpp)
target_link_libraries(objectDetectionTrainer dlib)



#########
# TESTS #
#########

# Create target for automated unit tests
add_executable(runCoreTests test/main/CoreTestRunner.cpp ${CORE_TEST_FILES} $<TARGET_OBJECTS:test_support>)
target_link_libraries(runCoreTests obstdetect_core ${TEST_FRAMEWORK_LIBS})

# IMU testing
add_executable(imuTest test/main/IMUTest.cpp)
target_link_libraries(imuTest obstdetect_full test_device)

# Display testing
add_executable(displayTest test/main/DisplayTest.cpp)
target_link_libraries(displayTest obstdetect_full test_device)

add_executable(displayVideoTest test/main/DisplayVideoTest.cpp)
target_link_libraries(displayVideoTest obstdetect_full test_device)

add_executable(displayInitTest test/main/DisplayInitializationTest.cpp)
target_link_libraries(displayInitTest obstdetect_full test_device)

# Lepton testing
add_executable(leptonShutter test/main/LeptonShutterTest.cpp)
target_link_libraries(leptonShutter obstdetect_full test_device)
