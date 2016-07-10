#include <exceptions/CameraDataDeserializationException.h>
#include "CameraDataSerializerTest.h"


TEST_F (CameraDataSerializerTest, serializeDeserialize) {
    CameraStatus camStatus1 = OK;
    Image16bit image1(_freighterSunImg, false);
    CameraData camData1 = {camStatus1, LeptonCameraSpecifications, image1};
    std::vector<CameraData> inputVector;
    inputVector.push_back(camData1);

    CameraStatus camStatus2 = SHUTTER_CLOSED;
    Image16bit image2(_garbledImg, false);
    CameraData camData2 = {camStatus2, LeptonCameraSpecifications, image2};
    inputVector.push_back(camData2);

    CameraStatus camStatus3 = OFF;
    Image16bit image3(_fishingBoatImg, false);
    CameraData camData3 = {camStatus3, LeptonCameraSpecifications, image3};
    inputVector.push_back(camData3);

    zmq::message_t message = CameraDataSerializer::serializeToZmq(inputVector);
    std::vector<CameraData> deserialized = CameraDataDeserializer::deserializeFromZmq(message);

    EXPECT_EQ(inputVector.size(), deserialized.size());

    for (int i = 0; i < inputVector.size(); i++) {
        CameraData pre = inputVector[i];
        CameraData post = deserialized[i];

        EXPECT_EQ(pre.status, post.status);
        EXPECT_EQ(pre.imageSpecs, post.imageSpecs);


        EXPECT_EQ(pre.frame, post.frame);
    }
}

TEST_F(CameraDataSerializerTest, throwOnEmptyMessage) {
    zmq::message_t message(0);
    EXPECT_THROW(CameraDataDeserializer::deserializeFromZmq(message),
                 CameraDataDeserializationException);
}

TEST_F(CameraDataSerializerTest, throwOnJunkMessage) {
    zmq::message_t message("1234567890", 10);

    EXPECT_THROW(CameraDataDeserializer::deserializeFromZmq(message),
                 CameraDataDeserializationException);
}
