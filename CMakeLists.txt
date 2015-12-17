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

###############
# EXECUTABLES #
###############

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