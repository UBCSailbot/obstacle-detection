//
// Created by root on 10/10/15.
//

#ifndef OBSTACLE_AVOIDANCE_INCORRECTIMAGETYPE_H
#define OBSTACLE_AVOIDANCE_INCORRECTIMAGETYPE_H

#include <stdexcept>

class IncorrectImageTypeException: public std::logic_error {

  public:
    IncorrectImageTypeException(const char *message) :
        std::logic_error::logic_error(message) { }

};

#endif //OBSTACLE_AVOIDANCE_INCORRECTIMAGETYPE_H
