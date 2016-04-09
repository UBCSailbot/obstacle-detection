#include "CameraDataSerializer.h"

zmq::message_t CameraDataSerializer::serializeToZmq(std::vector<CameraData> dataVector){

    size_t messageSize = 0;

    for (CameraData data : dataVector) {
        messageSize += sizeof(CameraStatus);
        messageSize += sizeof(CameraSpecifications);
        size_t imageSize = data.frame.cols * data.frame.rows * data.imageSpecs.bytesPerPixel;
        messageSize += imageSize;
    }

    zmq::message_t message(messageSize);
    char* messagePointer = (char*) message.data();

    for (CameraData data : dataVector){
        CameraStatus* statusPointer = &data.status;
        memcpy(messagePointer, statusPointer, sizeof(CameraStatus));
        messagePointer += sizeof(CameraStatus);

        CameraSpecifications * specsPointer = &data.imageSpecs;
        memcpy(messagePointer, specsPointer, sizeof(CameraSpecifications));
        messagePointer += sizeof(CameraSpecifications);

        int imageSize = data.frame.cols * data.frame.rows * 2;
        memcpy(messagePointer, data.frame.data, (size_t) imageSize);
        messagePointer += imageSize;
    }

    return message;
}
