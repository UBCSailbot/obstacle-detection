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

# Include the ZeroMQ pkgconfig
find_package(PkgConfig REQUIRED)
pkg_search_module(ZMQ REQUIRED libzmq)
list(APPEND CORE_LIBS ${ZMQ_LIBRARIES})
include_directories(${ZMQ_INCLUDE_DIRS})
link_directories(${ZMQ_LIBRARY_DIRS})

# Add the zmq.hpp file to the include path
include_directories(lib/cppzmq)

# dlib is compiled with the project
include(${CMAKE_SOURCE_DIR}/lib/dlib/dlib/cmake)
list(APPEND CORE_LIBS dlib)
