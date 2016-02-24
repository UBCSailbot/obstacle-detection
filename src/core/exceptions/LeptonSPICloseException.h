//
// Created by Amy Khosa on 15-11-05.
//

#ifndef OBSTACLE_AVOIDANCE_LEPTONSPICLOSEEXCEPTION_H
#define OBSTACLE_AVOIDANCE_LEPTONSPICLOSEEXCEPTION_H
#include <iostream>
#include <exception>

class LeptonSPICloseException: public std::exception {
  private:
    const char *closeErrMessage_;

  public:
    LeptonSPICloseException(const char *errMessage) :
        closeErrMessage_(errMessage) { };

    const char *what();
};

#endif //OBSTACLE_AVOIDANCE_LEPTONSPICLOSEEXCEPTION_H
