#########
# TESTS #
#########

# Add test folders to header search path so that we don't have to `#include` relative paths
include_directories( test/core )
include_directories( test/device )
include_directories( test/support )

# supporting files (coded by us) used across tests, both automated and manual
add_library(test_support STATIC test/support/ImageLoaderForTests.cpp)

add_library(unit_tests OBJECT 
	test/core/comm/AStoppableWorkerTest.cpp
	test/core/config/ConfigTest.cpp
	test/core/detect/ObstacleTest.cpp
	test/core/detect/SimpleDangerZoneEncoderTest.cpp
	test/core/features/HorizonImageTest.cpp
	test/core/features/SunImageTest.cpp
	test/core/geometry/CompareTest.cpp
	test/core/geometry/HorizonTest.cpp
	test/core/geometry/LineTest.cpp
	test/core/geometry/OrientationTest.cpp
	test/core/geometry/Vector2dTest.cpp
	test/core/imageProc/histogram/ImageHistogramTest.cpp
	test/core/imageProc/rescale/RescalingTest.cpp
	test/core/imageProc/smoothing/AveragedBufferedSmootherTest.cpp
	test/core/imageTypes/Image16bitTest.cpp
	test/core/imageTypes/Image8bitTest.cpp
	test/core/io/cameradata/CameraDataSerializerTest.cpp
	test/core/io/JSONSerializerTest.cpp
	test/core/io/OrientationFileReaderTest.cpp
	test/core/logger/LoggerTest.cpp
	test/core/paths/ResourcesTest.cpp
	test/core/imageProc/filters/RectangleComparatorTest.cpp
	test/core/io/DangerZoneSerializerTest.cpp
	test/core/io/bearingConverterTest.cpp
	test/core/io/cameradata/CameraDataProcessorTest.cpp)

# tests of code that interfaces with devices; generally can't be run automatically
add_library(test_device STATIC test/device/imu/MockIMU.cpp
	test/device/lepton/MockLepton.cpp)
