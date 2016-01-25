##################
# TEST FRAMEWORK #
##################

# Add google test framework
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/googletest/googletest gtest)
include_directories(gtest STATIC ${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include )

set(TEST_FRAMEWORK_LIBS gtest)