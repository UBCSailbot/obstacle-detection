#include "ThermalCameraStream.h"

ThermalCameraStream::ThermalCameraStream(Lepton camera) : _lepton(camera)
{
    _latestFrame = (uint16_t*) malloc(VIEWPORT_WIDTH_PIX * VIEWPORT_HEIGHT_PIX * sizeof(uint16_t));
    _newFrameAvailable = false;
    _canOverwriteLatestFrame = true;

    std::thread tempThread(&ThermalCameraStream::startCapture, this);
    std::swap(tempThread, _leptonThread);
}

ThermalCameraStream::~ThermalCameraStream() {
    free(_latestFrame);
}

Image16bit ThermalCameraStream::nextImage() {

    {
        std::unique_lock<std::mutex> lock(_mtx);
        if (!_newFrameAvailable){
            _cv.wait(lock);
        }
        _canOverwriteLatestFrame = false;
    }

    Image16bit frame(LeptonCameraSpecifications.pixelHeight,
                     LeptonCameraSpecifications.pixelWidth);

    for(int row=0; row < frame.rows; row++) {
        for (int col=0; col < frame.cols; col++) {
            frame.pixelAt(row, col) = _latestFrame[row * VIEWPORT_WIDTH_PIX + col];
        }
    }

    _newFrameAvailable = false;
    _canOverwriteLatestFrame = true;

    return frame;
}

void ThermalCameraStream::startCapture() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<float> elapsed_seconds;
    float leptonPeriodSeconds = 1 / LEPTON_FPS;

    // regularly poll the lepton
    while (1) {
        start = std::chrono::system_clock::now();

        /* Obtain the lock to check if allowed to overwrite the latest frame.
         *  If so, keep the lock until done overwriting it. */
        _mtx.lock();
        if (_canOverwriteLatestFrame) {

            _lepton.captureFrame(_latestFrame);
            _frameCounter++;

            if (_frameCounter >= 3) {
                _newFrameAvailable = true;
                _frameCounter = _frameCounter % 3;
            }

            _cv.notify_one();
        }
        _mtx.unlock();

        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;

        if (elapsed_seconds.count() < leptonPeriodSeconds) {
            unsigned int sleepTimeMicros = (unsigned int) (leptonPeriodSeconds - elapsed_seconds.count()) * 1000 * 1000;
            usleep(sleepTimeMicros);
        }

    }
}

bool ThermalCameraStream::hasNext() const {
    return true;
}

int ThermalCameraStream::getImageWidth() const {
    // TODO: Make these part of the Lepton class itself
    return LeptonCameraSpecifications.pixelWidth;
}

int ThermalCameraStream::getImageHeight() const {
    // TODO: Make these part of the Lepton class itself
    return LeptonCameraSpecifications.pixelHeight;
}
