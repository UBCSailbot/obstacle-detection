//
// Created by denis on 09/06/16.
//

#include "CameraDataProcessor.h"

#include <QtCore/QTS>
#include <highgui.h>
#include "CameraDataHandler.h"


CameraDataProcessor::CameraDataProcessor(CameraDataStream *stream, ParallelIMU *imu,
                                         DLibProcessor *dLibProcessor, CameraDataHandler *cameraDataHandler)
        : _keepRecording(true), _dlibProcessor(dLibProcessor), _cameraDataHandler(cameraDataHandler), _stream(stream) {

}


void CameraDataProcessor::run() {
    while (getKeepRecording()) {

        std::vector<CameraData> dataVector = _stream->nextImage();

        std::vector<std::pair<CameraData, std::vector<dlib::rectangle>>> dataRectPairs;
        for (CameraData data : dataVector) {
            if (data.status != OK) {
                continue;
            }
            auto detectedRectangles = _dlibProcessor->getObjectDetectionBoxes(data.frame);

            dataRectPairs.push_back(
                    std::pair<CameraData, std::vector<dlib::rectangle>>(*std::move(&data),detectedRectangles));
        }

        if (dataRectPairs.size() > 0) {
            //TODO implement real comparison
            _cameraDataHandler->onImageProcessed(dataVector, dataRectPairs[0].second);
        }
    }
}


void CameraDataProcessor::setKeepRecording(volatile bool keepRecording) {
    _keepRecording = keepRecording;
}


volatile bool CameraDataProcessor::getKeepRecording() const {
    return _keepRecording;
}



