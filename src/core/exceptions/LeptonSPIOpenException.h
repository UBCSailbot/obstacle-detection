//
// Created by Amy Khosa on 15-11-05.
//

#ifndef OBSTACLE_AVOIDANCE_LEPTONSPIOPENEXCEPTION_H
#define OBSTACLE_AVOIDANCE_LEPTONSPIOPENEXCEPTION_H
#include <iostream>
#include <exception>

class LeptonSPIOpenException: public std::exception {
  private:
    const char *errMessage_;

  public:
    LeptonSPIOpenException(const char *errMessage) :
        errMessage_(errMessage) { };

    const char *what();
};

#endif //OBSTACLE_AVOIDANCE_LEPTONSPIOPENEXCEPTION_H
