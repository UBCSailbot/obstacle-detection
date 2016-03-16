//
// Created by paul on 09/02/16.
//

#ifndef OBSTACLE_DETECTION_FILESYSTEMIMAGESTREAM_H
#define OBSTACLE_DETECTION_FILESYSTEMIMAGESTREAM_H


#include <vector>

#include <opencv2/highgui/highgui.hpp>

#include "exceptions/EndOfStreamException.h"
#include "paths/Paths.h"
#include "ImageStream.h"

/**
 * "Streams" pre-recorded images directly from the file system
 *  to simulate a camera stream offline.
 */
class FileSystemImageStream: public ImageStream {

  public:

    /**
     * PARAM: imageDirectory - a string describing the full path to a directory
     *  containing the image files from which to build the stream.
     * PARAM: imageFileFilter - a string expression indicating which files to
     *  use from the given directory. E.g. "*.png" matches all files whose names
     *  end with the .png file extension. "*" matches all files.
     */
    FileSystemImageStream(std::string imageDirectory, std::string imageFileFilter);

    Image16bit nextImage();

    bool hasNext() const;

    int getImageWidth() const;

    int getImageHeight() const;


  private:
    int _imgHeight, _imgWidth;

    std::string _imgDir;
    std::string _imgFileFilter;

    std::vector <std::string> _frameList;
    int _currIndex;
};


#endif //OBSTACLE_DETECTION_FILESYSTEMIMAGESTREAM_H
