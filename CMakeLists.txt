cmake_minimum_required(VERSION 2.8)
project(obstacle_avoidance)
include(ExternalProject)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


###########
# SOURCES #
###########

# Add src folders to header search path so that we don't have to `#include` relative paths
include_directories( src/core )
include_directories( src/device )

file(GLOB_RECURSE CORE_SOURCE_FILES src/core/*.cpp src/core/*.h)
file(GLOB_RECURSE DEVICE_SOURCE_FILES src/device/*.cpp src/device/*.h)

add_executable(rigRunner src/main/RigRunner.cpp ${CORE_SOURCE_FILES} ${DEVICE_SOURCE_FILES})

add_executable(liveFeeder src/main/LiveFeed.cpp ${CORE_SOURCE_FILES} ${DEVICE_SOURCE_FILES})

add_executable(rescale src/main/RunRescaling.cpp ${CORE_SOURCE_FILES})

add_executable(sunImageRunner src/main/SunImageRunner.cpp ${CORE_SOURCE_FILES})

add_executable(objectDetectionRunner src/main/ObjectDetectionRunner.cpp)

add_executable(objectDetectionTrainer src/main/ObjectDetectionTrainer.cpp)

add_executable(objectDetectionModelGenerator src/main/ObjectDetectionModelGenerator.cpp)

#########
# TESTS #
#########

# Add test folders to header search path so that we don't have to `#include` relative paths
include_directories( test/core )
include_directories( test/device )
include_directories( test/support )

file(GLOB_RECURSE CORE_TEST_FILES test/core/*.cpp test/core/*.h)
file(GLOB_RECURSE DEVICE_TEST_FILES test/device/*.cpp test/device/*.h)
file(GLOB_RECURSE SUPPORT_TEST_FILES test/support/*.cpp test/support/*.h)

set(CORE_TEST_FILES ${CORE_TEST_FILES} ${CORE_SOURCE_FILES} ${SUPPORT_TEST_FILES})
set(DEVICE_TEST_FILES ${DEVICE_TEST_FILES} ${DEVICE_SOURCE_FILES} ${SUPPORT_TEST_FILES})

# Create target for automated unit tests
add_executable(runCoreTests
               test/main/CoreTestRunner.cpp
               ${CORE_TEST_FILES}
)

# IMU testing
add_executable(imuTest
               test/main/IMUTest.cpp
               ${DEVICE_TEST_FILES}
)

# Display testing
add_executable(displayTest
               test/main/DisplayTest.cpp
               ${CORE_SOURCE_FILES}
               ${DEVICE_TEST_FILES}
)

add_executable(displayVideoTest
               test/main/DisplayVideoTest.cpp
               ${CORE_SOURCE_FILES}
               ${DEVICE_TEST_FILES}
)

add_executable(displayInitTest
               test/main/DisplayInitializationTest.cpp
               ${CORE_SOURCE_FILES}
               ${DEVICE_TEST_FILES}
)

# Lepton testing
add_executable(leptonShutter
               test/main/LeptonShutterTest.cpp
               ${CORE_SOURCE_FILES}
               ${DEVICE_TEST_FILES}
)

# The following command copies the resources folder into the binary directory,
#  making it possible to load resources from a relative path within the project
add_custom_target(migrateResources
                        COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/resources
                        ${CMAKE_BINARY_DIR}/resources
)
add_dependencies(runCoreTests migrateResources)
add_dependencies(displayInitTest migrateResources)

##################
# TEST FRAMEWORK #
##################

# Add google test framework
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/googletest/googletest gtest)
include_directories(gtest STATIC ${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include )

set(TEST_FRAMEWORK_LIBS gtest)

#################
# CORE LIBRARIES #
#################

set( CORE_LIBS )

# OpenCV must be independently preinstalled on the host machine
find_package (OpenCV REQUIRED)
list(APPEND CORE_LIBS ${OpenCV_LIBS} )

# We use QT for handling file system paths
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
list(APPEND CORE_LIBS ${QT_LIBRARIES})

# Include tclap - a header-only library for command-line parsing
include_directories( lib/tclap/include )


####################
# DEVICE LIBRARIES #
####################

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
   OUTPUT ${LEPTONSDK_DIR}/Debug/libLEPTON_SDK.a
   COMMAND echo doing stuff
   COMMAND make
   WORKING_DIRECTORY ${LEPTONSDK_DIR}
 )
add_custom_target(leptonSDK DEPENDS ${LEPTONSDK_DIR}/Debug/libLEPTON_SDK.a)


add_dependencies(displayTest leptonSDK)
add_dependencies(rigRunner leptonSDK)
add_dependencies(liveFeeder leptonSDK)
add_dependencies(leptonShutter leptonSDK)

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
add_dependencies(rigRunner rpusbdisp)
add_dependencies(liveFeeder rpusbdisp)
add_dependencies(displayTest rpusbdisp)
add_dependencies(displayInitTest rpusbdisp)
add_dependencies(displayVideoTest rpusbdisp)
add_dependencies(leptonShutter rpusbdisp)
list(APPEND DEVICE_LIBS ${RPUSBDISP_DIR}/build/output/rpusbdisp-drv.a)
list(APPEND DEVICE_LIBS ${RPUSBDISP_DIR}/build/output/librpusbdisp-drv.so)


# Threads library must be independently preinstalled on the host machine
find_package (Threads REQUIRED)
list(APPEND CORE_LIBS ${CMAKE_THREAD_LIBS_INIT})


###################
# LIBRARY LINKING #
###################

# Once all the libraries have been loaded, they can be linked to the
#  executables as necessary
target_link_libraries(rigRunner ${CORE_LIBS} ${DEVICE_LIBS})
target_link_libraries(liveFeeder ${CORE_LIBS} ${DEVICE_LIBS})
target_link_libraries(rescale ${CORE_LIBS})
target_link_libraries(sunImageRunner ${CORE_LIBS})

target_link_libraries(runCoreTests ${CORE_LIBS} ${TEST_FRAMEWORK_LIBS})


target_link_libraries(objectDetectionRunner dlib)
target_link_libraries(objectDetectionTrainer dlib)
target_link_libraries(objectDetectionModelGenerator dlib)

target_link_libraries(imuTest ${CORE_LIBS} ${DEVICE_LIBS})
target_link_libraries(displayTest ${CORE_LIBS} ${DEVICE_LIBS})
target_link_libraries(displayInitTest ${CORE_LIBS} ${DEVICE_LIBS})
target_link_libraries(displayVideoTest ${CORE_LIBS} ${DEVICE_LIBS})
target_link_libraries(leptonShutter ${CORE_LIBS} ${DEVICE_LIBS})
