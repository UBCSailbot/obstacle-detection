//
// Created by paul on 09/02/16.
//

#ifndef OBSTACLE_DETECTION_FILESYSTEMIMAGESTREAM_H
#define OBSTACLE_DETECTION_FILESYSTEMIMAGESTREAM_H


#include <vector>

#include <opencv2/highgui/highgui.hpp>

#include <exceptions/EndOfStreamException.h>
#include "Paths.h"
#include "ImageStream.h"

class FileSystemImageStream : public ImageStream {

public:
    FileSystemImageStream(std::string imageDirectory, std::string imageFileFilter);

    Image16bit nextImage();

    bool hasNext() const;

    int getImageWidth() const;

    int getImageHeight() const;


private:
    int _imgHeight, _imgWidth;

    std::string _imgDir;
    std::string _imgFileFilter;

    std::vector<std::string> _frameList;
    int _currIndex;
};


#endif //OBSTACLE_DETECTION_FILESYSTEMIMAGESTREAM_H
