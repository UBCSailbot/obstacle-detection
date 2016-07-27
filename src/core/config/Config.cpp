#include "config/Config.h"
#include "config/BadConfigException.h"

namespace od {

Config::adavision_config::ImageSource
Config::adavision_config::image_source() const {
    const auto modeString = config_["image_source"];

    if (modeString == "file") {
        return FILE;
    }
    else if (modeString == "network") {
        return NETWORK;
    }
    else {
        throw BadConfigException("Invalid value for adavision::image_source::source: "
                                 + modeString);
    }
}

Config::adavision_config::imu_config::ImuMode
Config::adavision_config::imu_config::mode() const {
    const auto modeString = config_["mode"];

    if (modeString == "stub") {
        return STUB;
    }
    else if (modeString == "real") {
        return REAL;
    }
    else {
        throw BadConfigException("Invalid value for adavision::imu::mode: "
                                 + modeString);
    }
}

Config::adavision_config::current_data_config::CurrentDataMode
Config::adavision_config::current_data_config::mode() const {
    const auto modeString = config_["mode"];

    if (modeString == "stub") {
        return STUB;
    }
    else if (modeString == "real") {
        return REAL;
    }
    else {
        throw BadConfigException("Invalid value for adavision::current_data::mode: "
                                 + modeString);
    }
}

Config::camera_enclosure_config::ImageSource
Config::camera_enclosure_config::image_source() const {
    const auto modeString = config_["image_source"];

    if (modeString == "file") {
        return FILE;
    }
    else if (modeString == "lepton") {
        return LEPTON;
    }
    else {
        throw BadConfigException("Invalid value for camera_enclosure::image_source::source: "
                                 + modeString);
    }
}

std::vector<Config::perception_config::ObjectDetectorType>
Config::perception_config::boat_detection_config::models_config::all() const {
    std::vector<ObjectDetectorType> detectors;

    const dlib::config_reader &models = config_;
    std::vector<std::string> keys;
    models.get_keys(keys);

    for (const auto &key : keys) {
        dlib::object_detector<DLibProcessor::image_scanner_type> detector;
        dlib::deserialize(models[key]) >> detector;
        detectors.push_back(detector);
    }

    return detectors;
}

} // od
