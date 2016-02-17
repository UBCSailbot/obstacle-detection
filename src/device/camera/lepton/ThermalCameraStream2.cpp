#include "ThermalCameraStream2.h"

ThermalCameraStream2::ThermalCameraStream2(Lepton camera) : _lepton(camera)
{
    _lastCaptureTime = std::chrono::system_clock::now();
    _frameBuffer = (uint16_t*) malloc(VIEWPORT_WIDTH_PIX * VIEWPORT_HEIGHT_PIX * sizeof(uint16_t));
    _periodSeconds = 3 / LEPTON_FPS;
}

ThermalCameraStream2::~ThermalCameraStream2() {
    free(_frameBuffer);
}

Image16bit ThermalCameraStream2::nextImage() {
    auto now = std::chrono::system_clock::now();
    auto elapsedSeconds = now - _lastCaptureTime;
    if (elapsedSeconds.count() < _periodSeconds) {
        // sleep
        unsigned int sleepTimeMicros = (unsigned int) (_periodSeconds - elapsedSeconds.count()) * 1000 * 1000;
        usleep(sleepTimeMicros);
    }

    return _lepton.captureFrame();

//    Image16bit frame(LeptonCameraSpecifications.pixelHeight,
//                     LeptonCameraSpecifications.pixelWidth);
//
//    for(int row=0; row < frame.rows; row++) {
//        for (int col=0; col < frame.cols; col++) {
//            frame.pixelAt(row, col) = _frameBuffer[row * VIEWPORT_WIDTH_PIX + col];
//        }
//    }
//
//
//    return frame;
}

bool ThermalCameraStream2::hasNext() const {
    return true;
}

int ThermalCameraStream2::getImageWidth() const {
    return LeptonCameraSpecifications.pixelWidth;
}

int ThermalCameraStream2::getImageHeight() const {
    return LeptonCameraSpecifications.pixelHeight;
}
