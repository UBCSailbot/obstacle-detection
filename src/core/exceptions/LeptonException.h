#ifndef OBSTACLE_AVOIDANCE_LEPTONSPIOPENEXCEPTION_H
#define OBSTACLE_AVOIDANCE_LEPTONSPIOPENEXCEPTION_H
#include <iostream>
#include <exception>

class LeptonException : public std::exception {
  private:
    const char *errMessage_;

  public:
    LeptonException(const char *errMessage) :
        errMessage_(errMessage) { };

    const char *what() const noexcept override;
};

#endif //OBSTACLE_AVOIDANCE_LEPTONSPIOPENEXCEPTION_H
