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

#Disable unneeded options for dlib
set(DLIB_USE_CUDA_STR OFF)
set(DLIB_USE_LAPACK_STR OFF)
set(DLIB_USE_BLAS_STR OFF)
# dlib is compiled with the project
include(${CMAKE_SOURCE_DIR}/lib/dlib/dlib/cmake)
list(APPEND CORE_LIBS dlib)

# For jsoncpp, first a "source code amalgamation" script is run if need be.
#  Then, a static library is built from that file.
include_directories(${CMAKE_SOURCE_DIR}/lib/jsoncpp/include)
set(JSONCPP_DIR ${CMAKE_SOURCE_DIR}/lib/jsoncpp)
set(JSONCPP_AMALG_SRC ${JSONCPP_DIR}/dist/jsoncpp.cpp)
add_custom_command(
        OUTPUT ${JSONCPP_AMALG_SRC}
        COMMAND python ${JSONCPP_DIR}/amalgamate.py
        WORKING_DIRECTORY ${JSONCPP_DIR}
        COMMENT "Amalgamating jsoncpp source code."
)
add_custom_target(jsoncpp_amalg DEPENDS ${JSONCPP_AMALG_SRC})
add_library(jsoncpp STATIC ${JSONCPP_AMALG_SRC})
add_dependencies(jsoncpp jsoncpp_amalg)
list(APPEND CORE_LIBS jsoncpp)
