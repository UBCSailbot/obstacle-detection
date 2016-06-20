#ifndef OBSTACLE_DETECTION_TOOMANYIMAGESEXCEPTION_H
#define OBSTACLE_DETECTION_TOOMANYIMAGESEXCEPTION_H


class TooManyImagesException: public std::logic_error {

public:
    TooManyImagesException(const char *message) : std::logic_error::logic_error(message) { }

};
#endif //OBSTACLE_DETECTION_TOOMANYIMAGESEXCEPTION_H
