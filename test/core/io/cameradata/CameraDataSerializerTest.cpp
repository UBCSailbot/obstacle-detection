#include "CameraDataSerializerTest.h"


TEST_F (CameraDataSerializerTest, serializeDeserialize) {
    CameraStatus camStatus1 = OK;
    Image16bit image1(_freighterSunImg, false);
    CameraData camData1 = {camStatus1, LeptonCameraSpecifications, image1};
    std::vector<CameraData> inputVector;
    inputVector.push_back(camData1);

    CameraStatus camStatus2 = OK;
    Image16bit image2(_garbledImg, false);
    CameraData camData2 = {camStatus2, LeptonCameraSpecifications, image2};
    inputVector.push_back(camData2);

    CameraStatus camStatus3 = OK;
    Image16bit image3(_fishingBoatImg, false);
    CameraData camData3 = {camStatus3, LeptonCameraSpecifications, image3};
    inputVector.push_back(camData3);

    zmq::message_t message = CameraDataSerializer::serializeToZmq(inputVector);
    std::vector<CameraData> deserialized = CameraDataDeserializer::deserializeFromZmq(message);

    compareVectors(inputVector, deserialized);
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

TEST_F(CameraDataSerializerTest, shutterClosedOrOff) {
    std::vector<CameraData> inputVector;
    CameraSpecifications emtpySpecs = {0, 0, 0, 0, 0};

    CameraStatus camStatus1 = SHUTTER_CLOSED;
    Image16bit image1;
    CameraData camData2 = {camStatus1, emtpySpecs, image1};
    inputVector.push_back(camData2);

    CameraStatus camStatus2 = OFF;
    Image16bit image2;
    CameraData camData3 = {camStatus2, emtpySpecs, image2};
    inputVector.push_back(camData3);

    zmq::message_t message = CameraDataSerializer::serializeToZmq(inputVector);
    std::vector<CameraData> deserialized = CameraDataDeserializer::deserializeFromZmq(message);

    compareVectors(inputVector, deserialized);
}

TEST_F(CameraDataSerializerTest, emptyImageSavesMemory) {
    CameraStatus status = OK;

    // Regular image
    std::vector<CameraData> nonEmptyVector;
    Image16bit realImage(_freighterSunImg, false);

    CameraData nonEmptyCamData = {status, LeptonCameraSpecifications, realImage};
    nonEmptyVector.push_back(nonEmptyCamData);


    // Empty image
    std::vector<CameraData> emptyVector;
    CameraSpecifications emptySpecs = {0, 0, 0, 0, 0};
    Image16bit emptyImage;

    CameraData emptyCamData = {status, emptySpecs, emptyImage};
    emptyVector.push_back(emptyCamData);

    zmq::message_t nonEmptyMessage = CameraDataSerializer::serializeToZmq(nonEmptyVector);
    zmq::message_t emptyMessage = CameraDataSerializer::serializeToZmq(emptyVector);

    // This will need to change if we ever introduce image compression into the
    //  serialization pipeline.
    size_t realImageSize = LeptonCameraSpecifications.pixelWidth *
                           LeptonCameraSpecifications.pixelHeight *
                           LeptonCameraSpecifications.bytesPerPixel;

    EXPECT_EQ(realImageSize, nonEmptyMessage.size() - emptyMessage.size());
}

void CameraDataSerializerTest::compareVectors(std::vector<CameraData> inputVector,
                                              std::vector<CameraData> deserialized)
{
    EXPECT_EQ(inputVector.size(), deserialized.size());

    for (int i = 0; i < inputVector.size(); i++) {
        CameraData pre = inputVector[i];
        CameraData post = deserialized[i];

        EXPECT_EQ(pre.status, post.status);
        EXPECT_EQ(pre.imageSpecs, post.imageSpecs);

        EXPECT_EQ(pre.frame, post.frame);
    }
}
