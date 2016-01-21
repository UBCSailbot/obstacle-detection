cmake_minimum_required(VERSION 2.8)
project(obstacle_detection)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


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
# of the UBC Sailbot obstacle detecton library: `obstdetect_core` and `obstdetect_full`.
include(src/src.cmake)

# include test files. This defines two intermediary targets: `test_core` and `test_device`.
include(test/test.cmake)

# defines the target `migrateResources`, used in tests
include(resources/res.cmake)



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




#########
# TESTS #
#########

# This is the target for running the entire suite of automated unit tests.
# (CORE_TEST_FILES must be added directly to this compilation unit for gtest to work properly.)
add_executable(runCoreTests test/main/CoreTestRunner.cpp ${CORE_TEST_FILES})
target_link_libraries(runCoreTests obstdetect_core test_core ${TEST_FRAMEWORK_LIBS})

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

# FileSystemImageStreamTest - streaming images from file system
add_executable(fsStreamTest test/main/FileSystemImageStreamTest.cpp)
target_link_libraries(fsStreamTest obstdetect_core test_core)

# Testing getting video from two leptons simultaneously over SPI
add_executable(twoLeptonsTest test/main/TwoLeptonsTest.cpp)
target_link_libraries(twoLeptonsTest obstdetect_full test_device)
