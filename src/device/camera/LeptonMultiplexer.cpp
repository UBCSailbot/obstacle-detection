#include <camera/lepton/LeptonRegistry.h>
#include "LeptonMultiplexer.h"

LeptonMultiplexer::LeptonMultiplexer(LeptonConfig leptonConfig, SunConfig sunConfig) :
        useLepton0_(leptonConfig.use_lepton0()),
        useLepton1_(leptonConfig.use_lepton1()),
        resetTimeDelayMillis_(leptonConfig.failure_behavior().reset_time_millis()),
        statusCheckIntervalSeconds_(leptonConfig.status_check_interval_s()),
        sunDutyCyclePercent_(leptonConfig.sun_behavior().sun_duty_cycle_percent()),
        sunPixelThreshold_(sunConfig.sun_pixel_threshold())
{
    std::thread _checkLeptonThread(&LeptonMultiplexer::checkLeptonStatus, this);
    _checkLeptonThread.detach();
}

std::vector<CameraData> LeptonMultiplexer::getLatestCameraData() {
    std::vector<CameraData> camDataVector;

    // If sun is present, the shutter stays open for
    // sunDutyCyclePercent_ frames, then closes until the number of frames
    // reaches 100, where it loops back.

    // First, we determine if the shutter(s) should be open
    // Note that sunDetected_ is set in the previous iteration (or to false
    // when the program first starts).
    if (frameCount_ == 0 && sunDetected_) {
        if (useLepton0_) {
            LeptonRegistry::getLepton0().openShutter();
        }
        if (useLepton1_) {
            LeptonRegistry::getLepton1().openShutter();
        }
        // Avoid rapid open/close:
        usleep(10000);
    }
    
    // Check to see if shutter should be closed
    if (frameCount_ == sunDutyCyclePercent_ && sunDetected_) {
        if (useLepton0_) {
            LeptonRegistry::getLepton0().closeShutter();
        }
        if (useLepton1_) {
            LeptonRegistry::getLepton1().closeShutter();
        }
        // Avoid rapid open/close:
        usleep(10000);
    }
    
    // If we are in the first part of the duty cycle, or the sun isn't detected,
    // we can take images like normal
    if (frameCount_ < sunDutyCyclePercent_ || !sunDetected_) {
        if (useLepton0_ && lepton0Connected_) {
            Image16bit image;
            CameraStatus cameraStatus;

            try {

                image = LeptonRegistry::getLepton0().captureFrame();
                sunDetected_ = imageHasSun(image);
                cameraStatus = OK;
            } 
            catch (const LeptonException &e) {
                cameraStatus = FAILED;
                if (lepton0Connected_) {
                    od::Logger::logInfo("Lepton 0 is disconnected");
                }
                lepton0Connected_ = false;
            }

            if (cameraStatus == OK) {
                CameraData camData = {cameraStatus, LeptonCameraSpecifications, image};
                camDataVector.push_back(camData);
            } else {
                CameraData failedCamData = {cameraStatus, FailedLeptonCameraSpecifications, image};
                camDataVector.push_back(failedCamData);
            }
        }
        
        if (useLepton1_ && lepton1Connected_) {

            Image16bit image;
            CameraStatus cameraStatus;

            try {

                image = LeptonRegistry::getLepton1().captureFrame();
                sunDetected_ = imageHasSun(image);
                cameraStatus = OK;
            } 
            catch (const LeptonException &e) {
                cameraStatus = FAILED;
                if (lepton1Connected_) {
                    od::Logger::logInfo("Lepton 1 is disconnected");
                }
                lepton1Connected_ = false;
            }

            if (cameraStatus == OK) {
                CameraData camData = {cameraStatus, LeptonCameraSpecifications, image};
                camDataVector.push_back(camData);
            } 
            else {
                CameraData failedCamData = {cameraStatus, FailedLeptonCameraSpecifications, image};
                camDataVector.push_back(failedCamData);
            }
        }
    }
        
    // If we are in the second part of the duty cycle and the sun is detected
    // we take an image, but discard it. The shutter should also be closed
    else if (frameCount_ >= sunDutyCyclePercent_ && sunDetected_) {
        if (useLepton0_ && lepton0Connected_) {
            try {
                LeptonRegistry::getLepton0().captureFrame();
            } 
            catch (const LeptonException &e) {
                if (lepton0Connected_) {
                    od::Logger::logInfo("Lepton 0 is disconnected");
                }
                lepton0Connected_ = false;
            }
        }

        if (useLepton1_ && lepton1Connected_) {
            try {
                LeptonRegistry::getLepton1().captureFrame();
            } 
            catch (const LeptonException &e) {
                if (lepton1Connected_) {
                    od::Logger::logInfo("Lepton 1 is disconnected");
                }
                lepton1Connected_ = false;
            }
        }
    }
    frameCount_ = (frameCount_ + 1) % 100;
    return camDataVector;
}

bool LeptonMultiplexer::imageHasSun(Image16bit image) {
    Horizon h(cv::Point2f(0, 0), cv::Point2f(LeptonCameraSpecifications.pixelWidth - 1, 0));
    // The last two arguments are not used
    SunImage sunImage = SunImage(h, image, sunPixelThreshold_, 0, 0);
    sunImage.findSunPosition();

    return sunImage.containsSun();
}

void LeptonMultiplexer::checkLeptonStatus() {
    while (!_terminate) {
        sleep(statusCheckIntervalSeconds_);

        if (!lepton0Connected_ && useLepton0_) {
            try {
                LeptonRegistry::getLepton0().resetVideoStream(resetTimeDelayMillis_ * 1000);
                // try getting a frame to see if we are still connected:
                LeptonRegistry::getLepton0().captureFrame();
                lepton0Connected_ = true;
                od::Logger::logInfo("Lepton 0 reconnected");
            }
            catch (const LeptonException &e) {

            }
        }
        if (!lepton1Connected_ && useLepton1_) {
            try {
                LeptonRegistry::getLepton1().resetVideoStream(resetTimeDelayMillis_ * 1000);
                // try getting a frame to see if we are still connected:
                LeptonRegistry::getLepton1().captureFrame();
                lepton1Connected_ = true;
                od::Logger::logInfo("Lepton 1 reconnected");
            }
            catch (const LeptonException &e) {

            }
        }

        if (_terminate) {
            break;
        }
    }
}
