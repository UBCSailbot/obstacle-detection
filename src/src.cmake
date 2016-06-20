###########
# SOURCES #
###########

# Add src folders to header search path so that we don't have to `#include` relative paths
include_directories(src/core)
include_directories(src/device)


#
# Add targets for separately compiling source files #
#

# src_core is the set of object files that are used by all variations of the obstacle detection library
add_library(src_core STATIC
        src/core/comm/AStoppableWorker.cpp
        src/core/comm/ImageFeedZmq.cpp
        src/core/comm/TCPCameraCommsPub.cpp
        src/core/comm/TCPCameraCommsSub.cpp
        src/core/comm/TCPImageServer.cpp
        src/core/comm/ZmqContextSingleton.cpp
        src/core/config/AdaVisionConfig.cpp
        src/core/config/BadConfigException.h
        src/core/detect/Obstacle.cpp
        src/core/detect/SimpleDangerZoneEncoder.cpp
        src/core/exceptions/ErrorMessageException.cpp
        src/core/exceptions/LeptonSPICloseException.cpp
        src/core/exceptions/LeptonSPIOpenException.cpp
        src/core/features/HorizonImage.cpp
        src/core/features/SunImage.cpp
        src/core/geometry/Compare.cpp
        src/core/geometry/Horizon.cpp
        src/core/geometry/HorizonFactory.cpp
        src/core/geometry/Line.cpp
        src/core/geometry/Orientation.cpp
        src/core/geometry/Vector2d.cpp
        src/core/imageProc/dlib/DLibProcessor.cpp
        src/core/imageProc/filters/RectangleComparator.cpp
        src/core/imageProc/histogram/HorizonImageHistogram.cpp
        src/core/imageProc/histogram/ImageHistogram.cpp
        src/core/imageProc/liveFeed/base64EncDec.cpp
        src/core/imageProc/liveFeed/Compressor.cpp
        src/core/imageProc/liveFeed/FeedReader.cpp
        src/core/imageProc/rescale/ClippingRescaler.cpp
        src/core/imageProc/rescale/Rescaling.cpp
        src/core/imageProc/rescale/SimpleRescaler.cpp
        src/core/imageProc/smoothing/WeightedAverageBufferedSmoother.cpp
        src/core/io/cameradata/CameraDataDeserializer.cpp
        src/core/io/cameradata/CameraDataImageStreamAdapter.cpp
        src/core/io/cameradata/CameraDataNetworkStream.cpp
        src/core/io/cameradata/CameraDataProcessor.cpp
        src/core/io/cameradata/CameraDataSerializer.cpp
        src/core/io/cameradata/ImageStreamCameraDataAdapter.cpp
        src/core/io/FileSystemImageStream.cpp
        src/core/io/JSONSerializer.cpp
        src/core/io/OrientationFileReader.cpp
        src/core/io/TCPImageStream.cpp
        src/core/paths/Paths.cpp
        src/core/paths/Resources.cpp
        src/core/types/CameraSpecifications.cpp
        src/core/types/Image16bit.cpp
        src/core/types/Image8bit.cpp
        src/core/types/message_types.h)
add_dependencies(src_core migrateResources)

# obstdetect_core is the version of the obstacle detection library stripped of any device-specific code
add_library(obstdetect_core STATIC "")
target_link_libraries(obstdetect_core src_core ${CORE_LIBS})

# obstdetect_full is the complete version of the obstacle detection library
add_library(obstdetect_full STATIC
        src/device/camera/lepton/Lepton.cpp
        src/device/camera/lepton/LeptonI2CConnection.cpp
        src/device/camera/lepton/LeptonRegistry.cpp
        src/device/camera/lepton/LeptonSPIConnection.cpp
        src/device/camera/lepton/ThermalCameraStream.cpp
        src/device/camera/LeptonMultiplexer.cpp
        src/device/camera/MockCameraMultiplexer.cpp
        src/device/display/DesktopDisplay.cpp
        src/device/display/DisplayUtils.cpp
        src/device/display/RoboPeakUSBDisplay.cpp
        src/device/imu/ParallelIMU.cpp
        )
target_link_libraries(obstdetect_full src_core ${CORE_LIBS} ${DEVICE_LIBS})
add_dependencies(obstdetect_full leptonSDK rpusbdisp)
# we don't add RTIMULib to the list of dependencies for obstdetect_full because it gets compiled automatically.
