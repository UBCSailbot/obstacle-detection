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
        auto time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());

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

        std::vector<cv::Rect> rectangles;
        switch (dataRectPairs.size()) {
            case 0:
                continue;
            case 1:
                rectangles = dataRectPairs[0].second;
                break;
            case 2:
                rectangles = RectangleComparator::getCommonRectangles(dataRectPairs[0].second, dataRectPairs[1].second);
                break;
            default:
                throw TooManyImagesException("More than 2 images received");
        }

        CameraSpecifications &specifications = dataVector[0].imageSpecs;
        HorizonFactory horizonFactory(specifications);
        Horizon horizon = horizonFactory.makeHorizon(orientation);

        filterRectanglesByHorizon(&rectangles, horizon);

        _cameraDataHandler.onImageProcessed(dataVector, rectangles, horizon);

        if (rectangles.size() > 0) {
            _cameraDataHandler.onDangerZoneProcessed(
                    getDangerZones(rectangles, frames, latestData, time, horizon, specifications));
        }
    }
}

void CameraDataProcessor::filterRectanglesByHorizon(std::vector<cv::Rect> *rectangles, const Horizon &horizon) {
    rectangles->erase(
            std::remove_if(rectangles->begin(), rectangles->end(),
                           [&horizon](const cv::Rect &elem) { return horizon.isRectAbove(elem); }),
            rectangles->end());
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
    points.push_back(cv::Point2f(rect.x + rect.width, rect.y));
    points.push_back(cv::Point2f(rect.x, rect.y + rect.height));

    return Obstacle(points, horizon);
}


std::vector<DangerZone> CameraDataProcessor::getDangerZones(const std::vector<cv::Rect> &detectedRectangles,
                                                            const std::vector<std::shared_ptr<cv::Mat>> &frames,
                                                            const CurrentData &latestData,
                                                            const std::chrono::duration<uint64_t, std::ratio<1, 1>> &imageReceiveTime,
                                                            const Horizon &horizon,
                                                            const CameraSpecifications &specs) {

    std::vector<Obstacle> obstacles;
    std::transform(detectedRectangles.begin(), detectedRectangles.end(), std::back_inserter(obstacles),
                   [&](const cv::Rect &elem) { return rectToObstacle(elem, horizon); });

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

