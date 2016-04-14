#ifndef OBSTACLE_DETECTION_CAMERADATASERIALIZERTEST_H
#define OBSTACLE_DETECTION_CAMERADATASERIALIZERTEST_H

#include <gtest/gtest.h>
#include <ImageLoaderForTests.h>
#include <types/CameraData.h>
#include <camera/lepton/LeptonCameraSpecifications.h>
#include <io/CameraDataSerializer.h>
#include <io/CameraDataDeserializer.h>

class CameraDataSerializerTest : public ImageLoaderForTests {
    //tests both CameraDataSerializer and CameraDataDeserializer
};


#endif //OBSTACLE_DETECTION_CAMERADATASERIALIZERTEST_H
