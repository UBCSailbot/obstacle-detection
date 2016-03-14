###########
# SOURCES #
###########

# Add src folders to header search path so that we don't have to `#include` relative paths
include_directories( src/core )
include_directories( src/device )

file(GLOB_RECURSE CORE_SOURCE_FILES src/core/*.cpp src/core/*.h src/core/comm/zmq.hpp)
file(GLOB_RECURSE DEVICE_SOURCE_FILES src/device/*.cpp src/device/*.h)


#
# Add targets for separately compiling source files #
#

# src_core is the set of object files that are used by all variations of the obstacle detection library
add_library(src_core OBJECT ${CORE_SOURCE_FILES})
add_dependencies(src_core migrateResources)

# obstdetect_core is the version of the obstacle detection library stripped of any device-specific code
add_library(obstdetect_core STATIC $<TARGET_OBJECTS:src_core>)
target_link_libraries(obstdetect_core ${CORE_LIBS})

# obstdetect_full is the complete version of the obstacle detection library
add_library(obstdetect_full STATIC $<TARGET_OBJECTS:src_core> ${DEVICE_SOURCE_FILES})
target_link_libraries(obstdetect_full ${CORE_LIBS} ${DEVICE_LIBS})
add_dependencies(obstdetect_full leptonSDK rpusbdisp)
# we don't add RTIMULib to the list of dependencies for obstdetect_full because it gets compiled automatically.
