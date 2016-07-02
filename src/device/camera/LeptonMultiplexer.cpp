#include <camera/lepton/LeptonRegistry.h>
#include "LeptonMultiplexer.h"

LeptonMultiplexer::LeptonMultiplexer(bool useLepton0, bool useLepton1, int resetTimeDelay, int sunPixelThreshold,
                                     double sunDutyCycle) :
        _useLepton0(useLepton0), _useLepton1(useLepton1), _resetTimeDelay(resetTimeDelay),
        _sunPixelThreshold(sunPixelThreshold), _sunDutyCycle(sunDutyCycle) {

    std::thread _checkLeptonThread(&LeptonMultiplexer::checkLeptonStatus, this);
    _checkLeptonThread.detach();

}

std::vector<CameraData> LeptonMultiplexer::getLatestCameraData() {
    std::vector<CameraData> camDataVector;

    // If sun is present, the shutter stays open for
    // _SUN_DUTY_CYCLE * 100 frames, then closes until the number of frames
    // reaches 100, where it loops back.

    // First, we determine if the shutter(s) should be open
    // Note that _sunDetected is set in the previous iteration (or to false
    // when the program first starts).
    if (_frameCount == 0 && _sunDetected) {
        if (_useLepton0) {
            LeptonRegistry::getLepton0().openShutter();
        }
        if (_useLepton1) {
            LeptonRegistry::getLepton1().openShutter();
        }
        // Avoid rapid open/close:
        usleep(10000);
    }
    // Check to see if shutter should be closed
    if (_frameCount == static_cast<int> (_sunDutyCycle * 100) && _sunDetected) {
        if (_useLepton0) {
            LeptonRegistry::getLepton0().closeShutter();
        }
        if (_useLepton1) {
            LeptonRegistry::getLepton1().closeShutter();
        }
        // Avoid rapid open/close:
        usleep(10000);
    }
    // If we are in the first part of the duty cycle, or the sun isn't detected,
    // we can take images like normal
    if (_frameCount < static_cast<int> (_sunDutyCycle * 100) || !_sunDetected) {
        if (_useLepton0 && _lepton0Connected) {
            Image16bit image;
            CameraStatus cameraStatus;

            try {

                image = LeptonRegistry::getLepton0().captureFrame();
                _sunDetected = imageHasSun(image);
                cameraStatus = OK;
            } catch (LeptonException e) {
                cameraStatus = FAILED;
                if (_lepton0Connected) {
                    od::Logger::logInfo("Lepton 0 is disconnected");
                }
                _lepton0Connected = false;
            }

            if (cameraStatus == OK) {
                CameraData camData = {cameraStatus, LeptonCameraSpecifications, image};
                camDataVector.push_back(camData);
            } else {
                CameraData failedCamData = {cameraStatus, FailedLeptonCameraSpecifications, image};
                camDataVector.push_back(failedCamData);
            }
        }
        if (_useLepton1 && _lepton1Connected) {

            Image16bit image;
            CameraStatus cameraStatus;

            try {

                image = LeptonRegistry::getLepton1().captureFrame();
                _sunDetected = imageHasSun(image);
                cameraStatus = OK;
            } catch (LeptonException e) {
                cameraStatus = FAILED;
                if (_lepton1Connected) {
                    od::Logger::logInfo("Lepton 1 is disconnected");
                }
                _lepton1Connected = false;
            }

            if (cameraStatus == OK) {
                CameraData camData = {cameraStatus, LeptonCameraSpecifications, image};
                camDataVector.push_back(camData);
            } else {
                CameraData failedCamData = {cameraStatus, FailedLeptonCameraSpecifications, image};
                camDataVector.push_back(failedCamData);
            }
        }
    }
    // If we are in the second part of the duty cycle and the sun is detected
    // we take an image, but discard it. The shutter should also be closed
    else if (_frameCount >= static_cast<int> (_sunDutyCycle * 100) && _sunDetected) {

        if (_useLepton0 && _lepton0Connected) {

            try {
                LeptonRegistry::getLepton0().captureFrame();
            } catch (LeptonException e) {
                if (_lepton0Connected) {
                    od::Logger::logInfo("Lepton 0 is disconnected");
                }
                _lepton0Connected = false;
            }
        }

        if (_useLepton1 && _lepton1Connected) {

            try {
                LeptonRegistry::getLepton1().captureFrame();
            } catch (LeptonException e) {
                if (_lepton1Connected) {
                    od::Logger::logInfo("Lepton 1 is disconnected");
                }
                _lepton1Connected = false;
            }
        }
    }
    _frameCount = (_frameCount + 1) % 100;
    return camDataVector;
}

bool LeptonMultiplexer::imageHasSun(Image16bit image) {
    Horizon h(cv::Point2f(0, 0), cv::Point2f(LeptonCameraSpecifications.pixelWidth - 1, 0));
    // The last two arguments are not used
    SunImage sunImage = SunImage(h, image, _sunPixelThreshold, 0, 0);
    sunImage.findSunPosition();

    if (sunImage.containsSun()) {
        return true;
    } else {
        return false;
    }
}


void LeptonMultiplexer::checkLeptonStatus() {
    while (!_terminate) {
        sleep(LEPTON_CHECK_WAIT_TIME_SECONDS);

        if (!_lepton0Connected && _useLepton0) {
            try {
                LeptonRegistry::getLepton0().resetVideoStream(_resetTimeDelay * 1000);
                // try getting a frame to see if we are still connected:
                LeptonRegistry::getLepton0().captureFrame();
                _lepton0Connected = true;
                od::Logger::logInfo("Lepton 0 reconnected");
            } catch (LeptonException e) {

            }
        }
        if (!_lepton1Connected && _useLepton1) {
            void checkLeptonStatus();
            try {
                LeptonRegistry::getLepton1().resetVideoStream(_resetTimeDelay * 1000);
                // try getting a frame to see if we are still connected:
                LeptonRegistry::getLepton1().captureFrame();
                _lepton1Connected = true;
                od::Logger::logInfo("Lepton 1 reconnected");
            } catch (LeptonException e) {

            }
        }
        if (_terminate) {
            break;
        }
    }
}
