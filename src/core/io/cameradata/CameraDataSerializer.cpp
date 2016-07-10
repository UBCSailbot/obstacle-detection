#include "CameraDataSerializer.h"

zmq::message_t CameraDataSerializer::serializeToZmq(std::vector<CameraData> dataVector) {

    uint8_t numCameraData = static_cast<uint8_t> (dataVector.size());
    size_t messageSize = calculateMessageSize(dataVector, numCameraData);

    zmq::message_t message(messageSize);
    char *messagePointer = static_cast<char *>(message.data());

    // first two bytes encode message type
    msg_validation_code *messageTypePtr = &CAMERA_DATA_VECTOR_MSG_CODE;
    memcpy(messagePointer, messageTypePtr, sizeof(msg_validation_code));
    messagePointer += sizeof(msg_validation_code);

    // next byte encodes number of CameraData in the message
    uint8_t *numCamDataPtr = &numCameraData;
    memcpy(messagePointer, numCamDataPtr, sizeof(uint8_t));
    messagePointer += sizeof(uint8_t);

    for (CameraData &data : dataVector) {
        CameraStatus *statusPointer = &data.status;
        memcpy(messagePointer, statusPointer, sizeof(CameraStatus));
        messagePointer += sizeof(CameraStatus);

        CameraSpecifications *specsPointer = &data.imageSpecs;
        memcpy(messagePointer, specsPointer, sizeof(CameraSpecifications));
        messagePointer += sizeof(CameraSpecifications);

        int imageSize = data.frame.cols * data.frame.rows * 2;
        memcpy(messagePointer, data.frame.data, static_cast<size_t>(imageSize));
        messagePointer += imageSize;
    }

    return message;
}

size_t CameraDataSerializer::calculateMessageSize(const std::vector<CameraData> &dataVector, uint8_t numCameraData) {
    // first two bytes of the message encode message type
    size_t messageSize = sizeof(msg_validation_code);
    // The next byte encodes the number of CameraData
    messageSize += sizeof(uint8_t);

    // the rest of the message contains the actual CameraData
    for (CameraData data : dataVector) {
        messageSize += sizeof(CameraStatus);
        messageSize += sizeof(CameraSpecifications);
        size_t imageSize = (size_t) (data.frame.cols * data.frame.rows * data.imageSpecs.bytesPerPixel);
        messageSize += imageSize;
    }

    return messageSize;
}
