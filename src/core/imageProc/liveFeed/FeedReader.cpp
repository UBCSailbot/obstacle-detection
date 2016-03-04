//
// Created by denis on 06/02/16.
//

#include <io/ImageStream.h>
#include <camera/lepton/LeptonCameraSpecifications.h>
#include "FeedReader.h"

void FeedReader::beforeCapture() {

}

void FeedReader::onImageRead(Image16bit image) {

}

void FeedReader::record() {
    Image16bit frame(LeptonCameraSpecifications.pixelHeight, LeptonCameraSpecifications.pixelWidth);

    beforeCapture();

    while (this->shouldRecord) {
        frame = this->stream->nextImage();
        onImageRead(frame);
    }
}


void FeedReader::startRecording() {
    shouldRecord = true;
}

void FeedReader::stopRecording() {
    shouldRecord = false;

}

