#ifndef OBSTACLE_DETECTION_MESSAGEPASSINGEXCEPTION_H
#define OBSTACLE_DETECTION_MESSAGEPASSINGEXCEPTION_H


#include <exception>
#include <string>

class ErrorMessageException : public std::exception {
public:
    ErrorMessageException(const std::string &errMessage);
    const char *what() const noexcept override;

private:
    const std::string _errMessage;
};


#endif //OBSTACLE_DETECTION_MESSAGEPASSINGEXCEPTION_H
