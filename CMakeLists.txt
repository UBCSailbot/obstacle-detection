cmake_minimum_required(VERSION 2.8)
project(obstacle_detection)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/opt/X11/include")


############
# INCLUDES #
############

# include libraries that are used more or less in all places throughout the code
include(lib/core_libs.cmake)

# include libraries for interacting with sensors and other peripherals
include(lib/device_libs.cmake)

# include unit test framework
include(lib/test_libs.cmake)

# include source files. This defines two intermediary targets, both of which are versions
# of the UBC Sailbot obstacle detection library: `obstdetect_core` and `obstdetect_full`.
include(src/src.cmake)

# include test files. This defines two intermediary targets: `unit_tests` and `test_device`.
include(test/test.cmake)

# defines the target `migrateResources`, used in tests
include(resources/res.cmake)


#########
# FLAGS #
#########

# Define the command-line flags that should be accessible to programs
option(SAILBOT_DEBUG "Whether to build the project with the SAILBOT_DEBUG variable defined at the preprocessor level" OFF)
if(SAILBOT_DEBUG)
  add_definitions(-DSAILBOT_DEBUG)
endif()


############
# PROGRAMS #
############

# NOTE: Each of these should be documented in its own source code.

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
target_link_libraries(objectDetectionTrainer dlib)

add_executable(objectDetectionModelGenerator src/main/ObjectDetectionModelGenerator.cpp)
target_link_libraries(objectDetectionModelGenerator dlib)

add_executable(objectDetectionBenchmark src/main/ObjectDetectionBenchmark.cpp)
target_link_libraries(objectDetectionBenchmark dlib)

add_executable(cameraServer src/main/CameraEnclosureServer.cpp)
target_link_libraries(cameraServer obstdetect_full test_support)

add_executable(singleImageCameraServer src/main/SingleImageCameraEnclosureServer.cpp)
target_link_libraries(singleImageCameraServer obstdetect_full test_support)

add_executable(horizonEval src/main/HorizonEval.cpp)
target_link_libraries(horizonEval obstdetect_core)

add_executable(adaVision src/main/AdaVision.cpp)
target_link_libraries(adaVision obstdetect_full test_support)

#########
# TESTS #
#########

# This is the target for running the entire suite of automated unit tests.
# (CORE_TEST_FILES must be added directly to this compilation unit for gtest to work properly.)
add_executable(runCoreTests test/main/CoreTestRunner.cpp $<TARGET_OBJECTS:unit_tests>)
target_link_libraries(runCoreTests obstdetect_core test_support ${TEST_FRAMEWORK_LIBS})

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
add_executable(leptonShutterTest test/main/LeptonShutterTest.cpp)
target_link_libraries(leptonShutterTest obstdetect_full test_device)

# Test closing shutter on two Leptons
add_executable(doubleLeptonShutterTest test/main/DoubleLeptonShutterTest.cpp)
target_link_libraries(doubleLeptonShutterTest obstdetect_full test_device)

# Sun detection test
add_executable(sunDetectionTest test/main/SunDetectionTest.cpp)
target_link_libraries(sunDetectionTest obstdetect_full test_device)

# Test the throwing an exception when capturing frames over SPI Connection
add_executable(SPIExceptionTest test/main/SPIExceptionTest.cpp)
target_link_libraries(SPIExceptionTest obstdetect_full test_device)

# Testing getting video from two leptons simultaneously over SPI
add_executable(twoLeptonsTest test/main/TwoLeptonsTest.cpp)
target_link_libraries(twoLeptonsTest obstdetect_full test_device)

# FileSystemImageStreamTest - streaming images from file system
add_executable(fsStreamTest test/main/FileSystemImageStreamTest.cpp)
target_link_libraries(fsStreamTest obstdetect_core test_support)

# ImageServerTest - streaming images from file system
add_executable(imageServerTest test/main/ImageServerTest.cpp)
target_link_libraries(imageServerTest obstdetect_core test_support)

# LeptonServerTest - streaming images from Lepton on another device
add_executable(leptonServerTest test/main/LeptonServerTest.cpp)
target_link_libraries(leptonServerTest obstdetect_core)

# TCPCameraCameraCommsTest - recieves reply from server, displays image
add_executable(TCPCameraCommsTest test/main/TCPCameraCommsTest.cpp)
target_link_libraries(TCPCameraCommsTest obstdetect_full)

# LoggerTest - just prints out a few sample log messages
add_executable(loggerSample test/main/LoggerSample.cpp)
target_link_libraries(loggerSample obstdetect_core)

# CurrentDataConnectionTest - just prints out currentData
add_executable(currentDataConnectionTest test/main/CurrentDataConnectionTest.cpp)
target_link_libraries(currentDataConnectionTest obstdetect_core)
