#include "MockCameraMultiplexer.h"

std::vector<CameraData> MockCameraMultiplexer::getLatestCameraData() {
    std::vector<CameraData> camDataVector;

    if (runNumber == 1) {
        CameraStatus camStatus1 = OK;
        Image16bit image1(_freighterSunImg, false);
        CameraData camData1 = {camStatus1, LeptonCameraSpecifications, image1};
        camDataVector.push_back(camData1);

        CameraStatus camStatus2 = SHUTTER_CLOSED;
        Image16bit image2(_garbledImg, false);
        CameraData camData2 = {camStatus2, LeptonCameraSpecifications, image2};
        camDataVector.push_back(camData2);
    } else if (runNumber == 2){
        CameraStatus camStatus2 = SHUTTER_CLOSED;
        Image16bit image2(_garbledImg, false);
        CameraData camData2 = {camStatus2, LeptonCameraSpecifications, image2};
        camDataVector.push_back(camData2);

        CameraStatus camStatus3 = OFF;
        Image16bit image3(_fishingBoatImg, false);
        CameraData camData3 = {camStatus3, LeptonCameraSpecifications, image3};
        camDataVector.push_back(camData3);

    } else if (runNumber == 3){
        CameraStatus camStatus1 = FAILED;
        Image16bit image1(_freighterSunImg, false);
        CameraData camData1 = {camStatus1, LeptonCameraSpecifications, image1};
        camDataVector.push_back(camData1);

        CameraStatus camStatus3 = OK;
        Image16bit image3(_fishingBoatImg, false);
        CameraData camData3 = {camStatus3, LeptonCameraSpecifications, image3};
        camDataVector.push_back(camData3);
    }

    runNumber++;
    if (runNumber > 3) {
        runNumber = 1;
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    return camDataVector;
}

MockCameraMultiplexer::MockCameraMultiplexer() {
    _fishingBoatImg = cv::imread(Resources::getImagePath("16bit/fishingBoat01.png"), CV_LOAD_IMAGE_UNCHANGED);
    _freighterSunImg = cv::imread(Resources::getImagePath("16bit/freighterAndSun01.png"), CV_LOAD_IMAGE_UNCHANGED);
    _garbledImg = cv::imread(Resources::getImagePath("16bit/garbled01.png"), CV_LOAD_IMAGE_UNCHANGED);
    runNumber = 1;
}
