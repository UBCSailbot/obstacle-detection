#include <imageProc/filters/RectangleComparator.h>
#include <geometry/HorizonFactory.h>
#include <io/BearingConverter.h>
#include "CameraDataProcessor.h"
#include "exceptions/TooManyImagesException.h"


CameraDataProcessor::CameraDataProcessor(CameraDataStream &stream, DLibProcessor &dLibProcessor,
                                         CameraDataHandler &cameraDataHandler, IMU &imu,
                                         BoatDataStream &boatDataStream)
        : _keepRecording(true), _dlibProcessor(dLibProcessor), _cameraDataHandler(cameraDataHandler), _stream(stream),
          _simpleDangerZoneEncoder(), _imu(imu), _boatDataStream(boatDataStream) {

}


void CameraDataProcessor::run() {
    while (getKeepRecording()) {

        std::vector<CameraData> dataVector = _stream.nextImage();
        CurrentData latestData = _boatDataStream.getBoatData();
        Orientation orientation = _imu.getOrientation();
        _cameraDataHandler.onOrientationReceived(orientation);
        auto time = std::chrono::duration_cast<std::chrono::seconds>( std::chrono::system_clock::now().time_since_epoch());

        std::vector<std::shared_ptr<cv::Mat>> frames;
        std::vector<std::pair<std::shared_ptr<CameraData>, std::vector<cv::Rect>>> dataRectPairs;
        for (const CameraData &data : dataVector) {
            if (data.status != OK) {
                continue;
            }
            auto detectedRectangles = _dlibProcessor.getObjectDetectionBoxes(data.frame);
            std::shared_ptr<CameraData> frame(new CameraData(data));
            frames.push_back(std::shared_ptr<cv::Mat>(new cv::Mat(data.frame)));
            dataRectPairs.push_back(std::make_pair(frame, detectedRectangles));
        }

        if (dataRectPairs.size() == 1) {
            std::vector<cv::Rect> &rectangles = dataRectPairs[0].second;
            _cameraDataHandler.onImageProcessed(dataVector, rectangles);
            if (rectangles.size() > 0) {
                _cameraDataHandler.onDangerZoneProcessed(
                        getDangerZones(frames, rectangles, dataVector[0].imageSpecs, latestData,
                                       orientation, time));
            }
        } else if (dataRectPairs.size() == 2) {
            auto filteredRectangles = RectangleComparator::getCommonRectangles(dataRectPairs[0].second,
                                                                               dataRectPairs[1].second);
            _cameraDataHandler.onImageProcessed(dataVector, filteredRectangles);
            if (filteredRectangles.size() > 0) {
                _cameraDataHandler.onDangerZoneProcessed(
                        getDangerZones(frames, filteredRectangles, dataVector[0].imageSpecs, latestData,
                                       orientation, time));
            }

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

Obstacle CameraDataProcessor::rectToObstacle(cv::Rect rect, Horizon horizon) {
    std::vector<cv::Point2f> points;
    points.push_back(rect.tl());
    points.push_back(rect.br());

    return Obstacle(points, horizon);
}


std::vector<DangerZone> CameraDataProcessor::getDangerZones(std::vector<std::shared_ptr<cv::Mat>> frames,
                                                            std::vector<cv::Rect> detectedRectangles,
                                                            CameraSpecifications specs,
                                                            CurrentData latestData,
                                                            Orientation orientation,
                                                            std::chrono::duration<uint64_t, std::ratio<1, 1>> imageReceiveTime) {
    HorizonFactory horizonFactory(specs);
    Horizon horizon = horizonFactory.makeHorizon(orientation);
    std::vector<Obstacle> obstacles;
    std::transform(detectedRectangles.begin(), detectedRectangles.end(), std::back_inserter(obstacles),
                   [&](cv::Rect elem) { return rectToObstacle(elem, horizon); });

    ObstaclePositionFrame obstaclePositionFrame(frames, horizon, specs, obstacles);

    std::vector<DangerZone> dangerZones(_simpleDangerZoneEncoder.identifyDangerZones(obstaclePositionFrame));

    std::transform(std::begin(dangerZones), std::end(dangerZones), std::begin(dangerZones),
                   [&](DangerZone dangerZone) {
                       DangerZone convertedDangerZone = BearingConverter::convertToAbsoluteBearing(dangerZone,
                                                                                                   latestData.heading());
                       convertedDangerZone.set_latitude(latestData.latitude());
                       convertedDangerZone.set_longitude(latestData.longitude());
                       convertedDangerZone.setTime(imageReceiveTime);
                       return convertedDangerZone;
                   });

    return dangerZones;

}

