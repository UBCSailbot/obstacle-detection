//
// Created by denis on 06/02/16.
//

#include <io/ImageStream.h>
#include <imu/ParallelIMU.h>
#include <imageProc/rescale/SimpleRescaler.h>
#include <fstream>
#include <iostream>
#include <io/JSONSerializer.h>
#include <camera/lepton/LeptonCameraSpecifications.h>
#include "FeedReader.h"
#include "base64EncDec.h"

void FeedReader::beforeCapture() {

}

void FeedReader::onImageRead(Image16bit image) {

}

void FeedReader::record() { Image16bit frame(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX);
    int frame_counter = 1;

    beforeCapture();

    while (this->shouldRecord) {
        // read only every 3rd frame ( the frames are triplets)
        if ((frame_counter % 3) == 0) {
            frame = this->stream->nextImage();

            onImageRead(frame);

        }

        frame_counter++;
    }

}

void FeedReader::startRecording() {
    shouldRecord = true;
    record();
}

void FeedReader::stopRecording() {
    shouldRecord = false;

}
