#ifndef OBSTACLE_DETECTION_BADCONFIGEXCEPTION_H
#define OBSTACLE_DETECTION_BADCONFIGEXCEPTION_H


#include <exceptions/ErrorMessageException.h>

class BadConfigException : public ErrorMessageException {

public:
    BadConfigException(const std::string &errMessage) :
            ErrorMessageException(errMessage) { }
};


#endif //OBSTACLE_DETECTION_BADCONFIGEXCEPTION_H
