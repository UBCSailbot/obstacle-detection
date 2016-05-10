#ifndef OBSTACLE_DETECTION_CAMERADATADESERIALIZATIONEXCEPTION_H
#define OBSTACLE_DETECTION_CAMERADATADESERIALIZATIONEXCEPTION_H

#include "ErrorMessageException.h"

class CameraDataDeserializationException : public ErrorMessageException {

public:
    CameraDataDeserializationException(const std::string &errMessage) :
            ErrorMessageException(errMessage) { }
};


#endif //OBSTACLE_DETECTION_CAMERADATADESERIALIZATIONEXCEPTION_H
