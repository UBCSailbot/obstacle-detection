#ifndef OBSTACLE_DETECTION_CAMERADATASERIALIZERTEST_H
#define OBSTACLE_DETECTION_CAMERADATASERIALIZERTEST_H

#include <gtest/gtest.h>
#include <ImageLoaderForTests.h>
#include <types/CameraData.h>
#include <camera/lepton/LeptonCameraSpecifications.h>
#include <io/cameradata/CameraDataSerializer.h>
#include <io/cameradata/CameraDataDeserializer.h>
#include <exceptions/CameraDataDeserializationException.h>

class CameraDataSerializerTest : public ImageLoaderForTests {
    //tests both CameraDataSerializer and CameraDataDeserializer
protected:
    void compareVectors(std::vector<CameraData> inputVector, std::vector<CameraData> deserialized);
};


#endif //OBSTACLE_DETECTION_CAMERADATASERIALIZERTEST_H
