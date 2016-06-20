#include <imageProc/filters/RectangleComparator.h>
#include "CameraDataProcessor.h"
#include "exceptions/TooManyImagesException.h"

CameraDataProcessor::CameraDataProcessor(CameraDataStream &stream,
                                         DLibProcessor &dLibProcessor, CameraDataHandler &cameraDataHandler)
        : _keepRecording(true), _dlibProcessor(dLibProcessor), _cameraDataHandler(cameraDataHandler), _stream(stream) {

}


void CameraDataProcessor::run() {
    while (getKeepRecording()) {

        std::vector<CameraData> dataVector = _stream.nextImage();

        std::vector<std::pair<CameraData *, std::vector<cv::Rect>>> dataRectPairs;
        for (CameraData data : dataVector) {
            if (data.status != OK) {
                continue;
            }
            auto detectedRectangles = _dlibProcessor.getObjectDetectionBoxes(data.frame);

            dataRectPairs.push_back(std::pair<CameraData *, std::vector<cv::Rect>>(&data, detectedRectangles));
        }

        if (dataRectPairs.size() == 1) {
            _cameraDataHandler.onImageProcessed(dataVector, dataRectPairs[0].second);
        } else if (dataRectPairs.size() == 2) {
            auto filteredRectangles = RectangleComparator::getCommonRectangles(dataRectPairs[0].second,
                                                                               dataRectPairs[1].second);
            _cameraDataHandler.onImageProcessed(dataVector, filteredRectangles);
        } else if (dataRectPairs.size() > 2) {
            throw TooManyImagesException("More than 2 images received");
        }
    }
}


void CameraDataProcessor::setKeepRecording(volatile bool keepRecording) {
    _keepRecording = keepRecording;
}


volatile bool CameraDataProcessor::getKeepRecording() const {
    return _keepRecording;
}