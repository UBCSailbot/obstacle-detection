#include "CameraDataDeserializer.h"

std::vector<CameraData> CameraDataDeserializer::deserializeFromZmq(zmq::message_t &message) {
    std::vector<CameraData> dataVector;
    
    char* currentPos = (char*) message.data();
    char* endPoint = currentPos + message.size();

    while (currentPos < endPoint) {
        CameraStatus status = *((CameraStatus *) currentPos);
        currentPos += sizeof(CameraStatus);

        CameraSpecifications imageSpecs = *((CameraSpecifications *) currentPos);
        currentPos += sizeof(CameraSpecifications);

        int imageHeight = imageSpecs.pixelHeight;
        int imageWidth = imageSpecs.pixelWidth;
        size_t imageSize = (size_t) imageHeight * imageWidth * imageSpecs.bytesPerPixel;

        /*
         * Makes a copy of the image data sitting in the zmq message because
         *  the zmq message's data will be deallocated by the message's
         *  destructor.
         */
        Image16bit newImage(imageHeight, imageWidth, currentPos);

        CameraData camData = {status, imageSpecs, newImage};
        currentPos += imageSize;
        dataVector.push_back(camData);
    }

    return dataVector;
}