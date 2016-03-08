#include "ThermalCameraStream.h"

ThermalCameraStream::ThermalCameraStream(Lepton& camera) : _lepton(camera) {
    _lastCaptureTime = std::chrono::system_clock::now();
    _frameBuffer = (uint16_t *) malloc(LeptonCameraSpecifications.pixelWidth * LeptonCameraSpecifications.pixelHeight * sizeof(uint16_t));
    _periodSeconds = Lepton::REPEATING_FRAMES / Lepton::FPS;
}

ThermalCameraStream::~ThermalCameraStream() {
    free(_frameBuffer);
}

Image16bit ThermalCameraStream::nextImage() {
    auto now = std::chrono::system_clock::now();
    auto elapsedSeconds = now - _lastCaptureTime;

    if (elapsedSeconds.count() < _periodSeconds) {
        unsigned int sleepTimeMicros = (unsigned int) (_periodSeconds - elapsedSeconds.count()) * 1000 * 1000;
        usleep(sleepTimeMicros);
    }

    return _lepton.captureFrame();
}

bool ThermalCameraStream::hasNext() const {
    return true;
}

int ThermalCameraStream::getImageWidth() const {
    return LeptonCameraSpecifications.pixelWidth;
}

int ThermalCameraStream::getImageHeight() const {
    return LeptonCameraSpecifications.pixelHeight;
}
