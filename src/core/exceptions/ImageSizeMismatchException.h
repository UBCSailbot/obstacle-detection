//
// Created by paul on 17/12/15.
//

#ifndef OBSTACLE_DETECTION_IMAGESIZEMISMATCHEXCEPTION_H
#define OBSTACLE_DETECTION_IMAGESIZEMISMATCHEXCEPTION_H

#include <stdexcept>
#include <sstream>

class ImageSizeMismatchException: public std::logic_error {

  public:
    ImageSizeMismatchException(const char *message) :
        std::logic_error::logic_error(message) { }

    ImageSizeMismatchException(const int srcWidth, const int srcHeight,
                               const int dstWidth, const int dstHeight) :
        std::logic_error::logic_error(generateMessage(srcWidth, srcHeight, dstWidth, dstHeight)) { }

  private:
    const char *generateMessage(const int srcWidth, const int srcHeight, const int dstWidth, const int dstHeight) {
        std::stringstream ss;
        ss << "Expected image of size " << srcWidth << "x" << srcHeight <<
            ", but instead received image of size " << dstWidth << "x" << dstHeight << ".";
        return ss.str().c_str();
    }

};

#endif //OBSTACLE_DETECTION_IMAGESIZEMISMATCHEXCEPTION_H
