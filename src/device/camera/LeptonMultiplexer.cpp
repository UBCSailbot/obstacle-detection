#include <camera/lepton/LeptonRegistry.h>
#include "LeptonMultiplexer.h"

LeptonMultiplexer::LeptonMultiplexer(bool useLepton0, bool useLepton1, int RESET_TIME_DELAY) :
        _useLepton0(useLepton0), _useLepton1(useLepton1), _RESET_TIME_DELAY(RESET_TIME_DELAY) {
    std::thread _checkLeptonThread(&LeptonMultiplexer::checkLeptonStatus, this);
    _checkLeptonThread.detach();
}

std::vector<CameraData> LeptonMultiplexer::getLatestCameraData() {
    std::vector<CameraData> camDataVector;

    if (_useLepton0 && _lepton0Connected) {
        Image16bit image;
        CameraStatus cameraStatus;

        try {
            image = LeptonRegistry::getLepton0().captureFrame();
            cameraStatus = OK;
        } catch (LeptonException e) {
            cameraStatus = FAILED;
            if (_lepton0Connected) {
                std::cout << "Lepton 0 is disconnected" << std::endl;
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
            cameraStatus = OK;
        } catch (LeptonException e) {
            cameraStatus = FAILED;
            if (_lepton1Connected) {
                std::cout << "Lepton 1 is disconnected" << std::endl;
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

    return camDataVector;
}

void LeptonMultiplexer::checkLeptonStatus() {
    while (!_terminate) {
        sleep(LEPTON_CHECK_WAIT_TIME_SECONDS);

        if (!_lepton0Connected) {
            try {
                LeptonRegistry::getLepton0().resetVideoStream(_RESET_TIME_DELAY * 1000);
                // try getting a frame to see if we are still connected:
                LeptonRegistry::getLepton0().captureFrame();
                _lepton0Connected = true;
                std::cout << "Lepton 0 reconnected" << std::endl;
            } catch (LeptonException e) {

            }
        }
        if (!_lepton1Connected) {
            try {
                LeptonRegistry::getLepton1().resetVideoStream(_RESET_TIME_DELAY * 1000);
                // try getting a frame to see if we are still connected:
                LeptonRegistry::getLepton1().captureFrame();
                _lepton1Connected = true;
                std::cout << "Lepton 1 reconnected" << std::endl;
            } catch (LeptonException e) {

            }
        }
        if (_terminate) {
            break;
        }
    }
}
