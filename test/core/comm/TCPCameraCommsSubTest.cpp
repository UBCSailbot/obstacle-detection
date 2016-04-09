#include "TCPCameraCommsSubTest.h"

TEST_F (TCPCameraCommsSubTest, camSpecsAndPointers)
{
    CameraSpecifications dummySpecs = {1, 2, 2, 2.0, 3.0};
    CameraSpecifications * source = &dummySpecs;
    CameraSpecifications * destination = (CameraSpecifications *) malloc(sizeof(CameraSpecifications));
    memcpy(destination, source, sizeof(CameraSpecifications));

    CameraSpecifications actualSpecs = *destination;

    EXPECT_EQ(dummySpecs.pixelHeight, actualSpecs.pixelHeight);
    EXPECT_EQ(dummySpecs.pixelWidth, actualSpecs.pixelWidth);
    EXPECT_EQ(dummySpecs.FOVDegreesHorizontal, actualSpecs.FOVDegreesHorizontal);
    EXPECT_EQ(dummySpecs.FOVDegreesVertical, actualSpecs.FOVDegreesVertical);
}