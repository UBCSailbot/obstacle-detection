#ifndef OBSTACLE_DETECTION_ZMQEXCEPTION_H
#define OBSTACLE_DETECTION_ZMQEXCEPTION_H

#include "ErrorMessageException.h"

class ZmqException : public ErrorMessageException {
public:
    ZmqException(const std::string &errMessage) : ErrorMessageException(errMessage) {}
};

#endif //OBSTACLE_DETECTION_ZMQEXCEPTION_H
