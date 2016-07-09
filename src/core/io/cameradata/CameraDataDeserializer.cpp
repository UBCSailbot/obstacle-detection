#include "CameraDataDeserializer.h"

std::vector<CameraData> CameraDataDeserializer::deserializeFromZmq(zmq::message_t &message) {
    checkNonEmptyMessage(message);
    std::vector<CameraData> dataVector;

    char *currentPos = static_cast<char *>( message.data());
    char *endPoint = currentPos + message.size();

    msg_validation_code code = *(msg_validation_code *) currentPos;
    checkMessageCode(code);
    currentPos += sizeof(msg_validation_code);

    uint8_t actualNumCameraData = 0;
    uint8_t expectedNumCameraData = *((uint8_t *) currentPos);
    currentPos += sizeof(uint8_t);

    while (currentPos < endPoint) {
        CameraStatus status = *((CameraStatus *) currentPos);
        currentPos += sizeof(CameraStatus);
        if (currentPos >= endPoint) break;

        CameraSpecifications imageSpecs = *((CameraSpecifications *) currentPos);
        currentPos += sizeof(CameraSpecifications);
        if (currentPos >= endPoint) break;

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
        actualNumCameraData++;
    }

    checkNumberOfCameraDatas(expectedNumCameraData, actualNumCameraData);
    checkForOverflow(currentPos, endPoint);

    return dataVector;
}

void CameraDataDeserializer::checkNonEmptyMessage(const zmq::message_t &message) {
    if (message.size() <= 0) {
        throw CameraDataDeserializationException("Cannot deserialize message"
                                                         "of size 0.");
    }
}

void CameraDataDeserializer::checkMessageCode(msg_validation_code code) {
    if (!code == CAMERA_DATA_VECTOR_MSG_CODE) {
        throw CameraDataDeserializationException(
                "Received a message that does not appear to contain a vector"
                        " of CameraData.");
    }
}

void CameraDataDeserializer::checkNumberOfCameraDatas(size_t expected, size_t actual) {
    if (expected != actual) {
        std::stringstream ss;
        ss << "Deserialization of CameraData failed: expected " <<
        expected << " items, but instead found " <<
        actual << ".";
        throw CameraDataDeserializationException(ss.str());
    }
}

void CameraDataDeserializer::checkForOverflow(char *currentPos, char *endPoint) {
    if (currentPos > endPoint) {
        throw CameraDataDeserializationException("Inconsistency in counting "
                                                         "message size.");
    }
}







