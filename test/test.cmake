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

# supporting files (coded by us) used across tests, both automated and manual
add_library(test_support OBJECT ${SUPPORT_TEST_FILES})
add_dependencies(test_support migrateResources)

# tests of code that interfaces with devices; generally can't be run automatically
add_library(test_device STATIC $<TARGET_OBJECTS:test_support> ${DEVICE_TEST_FILES})


