#include <camera/lepton/LeptonRegistry.h>
#include "LeptonMultiplexer.h"

std::vector<CameraData> LeptonMultiplexer::getLatestCameraData() {
    std::vector<CameraData> camDataVector;

    if (_useLepton0) {
        Image16bit image = LeptonRegistry::getLepton0().captureFrame();
        // TODO: Return actual CameraStatus based on current status of camera
        CameraData camData = {OK, LeptonCameraSpecifications, image };
        camDataVector.push_back(camData);
    }
    if (_useLepton1) {
        Image16bit image = LeptonRegistry::getLepton1().captureFrame();
        // TODO: Return actual CameraStatus based on current status of camera
        CameraData camData = {OK, LeptonCameraSpecifications, image };
        camDataVector.push_back(camData);
    }

    return camDataVector;
}

LeptonMultiplexer::LeptonMultiplexer(bool useLepton0, bool useLepton1) :
        _useLepton0(useLepton0), _useLepton1(useLepton1) {

}
