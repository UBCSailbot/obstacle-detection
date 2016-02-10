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

void FeedReader::onImageRead(Image8bit image) {

}

void FeedReader::record() {
    ParallelIMU imu;
    SimpleRescaler rescaler;

    Image16bit frame(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX);
    Image8bit displayed(60, 80);
    int frame_counter = 1;
    char img_name[128];
    char imu_file_name[128];

    beforeCapture();

    while (this->shouldRecord) {
        // read only every 3rd frame ( the frames are triplets)
        if ((frame_counter % 3) == 0) {
            this->stream->getFrame(frame);

            // convert to 8 bit and display
            rescaler.scale16bitTo8bit(frame, displayed);

            onImageRead(displayed);

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
