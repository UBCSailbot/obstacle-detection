//
// Created by paul on 09/02/16.
//

#ifndef OBSTACLE_DETECTION_ENDOFSTREAMEXCEPTION_H
#define OBSTACLE_DETECTION_ENDOFSTREAMEXCEPTION_H

#include <exception>

class EndOfStreamException : public std::exception {

public:
    EndOfStreamException() {}
};

#endif //OBSTACLE_DETECTION_ENDOFSTREAMEXCEPTION_H
