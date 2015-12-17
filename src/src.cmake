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

add_dependencies(obstdetect_full leptonSDK rpusbdisp)

target_link_libraries(obstdetect_core ${CORE_LIBS})
target_link_libraries(obstdetect_full ${CORE_LIBS} ${DEVICE_LIBS})