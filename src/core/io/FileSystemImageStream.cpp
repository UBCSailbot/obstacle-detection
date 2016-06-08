//
// Created by paul on 09/02/16.
//

#include "FileSystemImageStream.h"

FileSystemImageStream::FileSystemImageStream(std::string imageDirectory,
                                             std::string imageFileFilter) :
    _imgDir(imageDirectory), _imgFileFilter(imageFileFilter) {
    _frameList = Paths::generateListOfFiles(imageDirectory, imageFileFilter);
    std::string firstImageFile = Paths::join(_imgDir, _frameList[0]);
    Image16bit tmp(cv::imread(firstImageFile, -1), false);

    _imgHeight = tmp.rows;
    _imgWidth = tmp.cols;

    _currIndex = 0;
}

Image16bit FileSystemImageStream::nextImage() {
    if (!hasNext()) {
        throw EndOfStreamException();
    }

    std::string nextImagePath = Paths::join(_imgDir, _frameList[_currIndex]);
    Image16bit currentImage = Image16bit(cv::imread(nextImagePath, -1), false);
    _currIndex++;
    return currentImage;
}

bool FileSystemImageStream::hasNext() const {
    return _currIndex < _frameList.size();
}

int FileSystemImageStream::getImageWidth() const {
    return _imgWidth;
}

int FileSystemImageStream::getImageHeight() const {
    return _imgHeight;
}
