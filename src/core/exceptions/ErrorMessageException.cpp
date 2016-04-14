#include "ErrorMessageException.h"

ErrorMessageException::ErrorMessageException(const std::string &errMessage) :
        _errMessage(errMessage) { }

const char *ErrorMessageException::what() const {
    return _errMessage.c_str();
}
