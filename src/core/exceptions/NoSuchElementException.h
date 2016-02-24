//
// Created by paul on 17/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_NOSUCHELEMENTEXCEPTION_H
#define OBSTACLE_AVOIDANCE_NOSUCHELEMENTEXCEPTION_H

#include <stdexcept>

class NoSuchElementException: public std::logic_error {

  public:
    NoSuchElementException(const char *message) :
        std::logic_error::logic_error(message) { }

};

#endif //OBSTACLE_AVOIDANCE_NOSUCHELEMENTEXCEPTION_H
