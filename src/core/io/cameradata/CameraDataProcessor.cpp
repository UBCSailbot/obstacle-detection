//
// Created by denis on 09/06/16.
//

#include "CameraDataProcessor.h"

#include <QtCore/QTS>
#include <highgui.h>
#include "CameraDataHandler.h"


CameraDataProcessor::CameraDataProcessor(CameraDataStream *stream, ParallelIMU *imu,
                                         DLibProcessor *dLibProcessor, CameraDataHandler* cameraDataHandler)
        : _keepRecording(true), _dLibProcessor(dLibProcessor), _cameraDataHandler(cameraDataHandler), _stream(stream) {

}


void CameraDataProcessor::run() {
    while (getKeepRecording()) {
        std::vector<CameraData> dataVector = _stream->nextImage();

        int numberOK =0;
        //This should filter out failed lepton data
        for (CameraData data : dataVector) {
            if (data.status == OK) {
                numberOK ++;
            }
        }

        if (numberOK == 1) {
            CameraData* image = &dataVector[0];
            if(dataVector.size() > 1) {
                CameraData *image1 = &dataVector[1];
                if (image->status != OK && image1->status == OK) {
                    image = image1;
                } else{
                    break;
                }
            }

            std::vector<dlib::rectangle> detectedRectangles = _dLibProcessor->getObjectDetectionBoxes(image->frame);
            _cameraDataHandler->onSingleImageProcessed(*image, detectedRectangles);
        } else if (numberOK == 2) {
            CameraData &image0 = dataVector[0];
            CameraData &image1 = dataVector[1];

            std::vector<dlib::rectangle> detectedRectangles0 = _dLibProcessor->getObjectDetectionBoxes(image0.frame);
            std::vector<dlib::rectangle> detectedRectangles1 = _dLibProcessor->getObjectDetectionBoxes(image1.frame);

            //TODO implement real comparison
            _cameraDataHandler->onMultiImageProcessed(dataVector, detectedRectangles0);
        }

    }
}

void CameraDataProcessor::setKeepRecording(volatile bool keepRecording) {
    _keepRecording = keepRecording;
}


volatile bool CameraDataProcessor::getKeepRecording() const {
    return _keepRecording;
}



