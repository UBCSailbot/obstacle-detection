#include <imageProc/dlib/DLibProcessor.h>
#include "AdaVisionConfig.h"
#include "BadConfigException.h"

AdaVisionConfig::AdaVisionConfig(const std::string &configFilePath) :
        config_(configFilePath)
{ }

AdaVisionConfig::Global AdaVisionConfig::global() const {
    return AdaVisionConfig::Global(config_.block("global"));
}

AdaVisionConfig::ImageSource AdaVisionConfig::imageSource() const {
    return AdaVisionConfig::ImageSource(config_.block("image_source"));
}

AdaVisionConfig::Output AdaVisionConfig::output() const {
    return AdaVisionConfig::Output(config_.block("output"));
}

bool AdaVisionConfig::Global::debug() const {
    return dlib::get_option(globalConfig_, "debug", false);
}


AdaVisionConfig::Global::Global(const dlib::config_reader &config) :
        globalConfig_(config)
{ }


AdaVisionConfig::ImageSource::ImageSource(const dlib::config_reader &config) :
        imageSourceConfig_(config)
{ }

AdaVisionConfig::ImageSource::Source AdaVisionConfig::ImageSource::source() const {
    const auto modeString = imageSourceConfig_["source"];

    if (modeString == "file") {
        return FILE;
    }
    else if (modeString == "network") {
        return NETWORK;
    }
    else {
        throw BadConfigException("Invalid value for image_source::source: "
                                 + modeString);
    }
}

AdaVisionConfig::ImageSource::File AdaVisionConfig::ImageSource::file() const {
    return ImageSource::File(imageSourceConfig_.block("file"));
}

AdaVisionConfig::ImageSource::Network AdaVisionConfig::ImageSource::network() const {
    return ImageSource::Network(imageSourceConfig_.block("network"));
}

AdaVisionConfig::ImageSource::File::File(const dlib::config_reader &config) :
        fileConfig_(config)
{ }


std::string AdaVisionConfig::ImageSource::File::inputDir() const {
    return fileConfig_["input_dir"];
}

bool AdaVisionConfig::ImageSource::File::doubleUp() const {
    return dlib::get_option(fileConfig_, "double_up", false);
}

AdaVisionConfig::ImageSource::Network::Network(const dlib::config_reader &config) :
        networkConfig_(config)
{ }

std::string AdaVisionConfig::ImageSource::Network::imagePubIP() const {
    return networkConfig_["image_pub_ip"];
}

std::string AdaVisionConfig::ImageSource::Network::imagePubPort() const {
    return networkConfig_["image_pub_port"];
}

AdaVisionConfig::MachineLearning AdaVisionConfig::machineLearning() const {
    return AdaVisionConfig::MachineLearning(config_.block("machine_learning"));
}

AdaVisionConfig::MachineLearning::MachineLearning(const dlib::config_reader &config) :
        mlConfig_(config)
{ }

AdaVisionConfig::MachineLearning::Models AdaVisionConfig::MachineLearning::models() const {
    return MachineLearning::Models(mlConfig_.block("models"));
}

std::vector<AdaVisionConfig::MachineLearning::ObjectDetectorType>
AdaVisionConfig::MachineLearning::Models::all() const {
    std::vector<ObjectDetectorType> detectors;

    const dlib::config_reader &models = modelsConfig_;
    std::vector<std::string> keys;
    models.get_keys(keys);

    for (const auto &key : keys) {
        dlib::object_detector<DLibProcessor::image_scanner_type> detector;
        dlib::deserialize(models[key]) >> detector;
        detectors.push_back(detector);
    }

    return detectors;
}

AdaVisionConfig::MachineLearning::ObjectDetectorType
AdaVisionConfig::MachineLearning::Models::boatDetector() const {
    dlib::object_detector<DLibProcessor::image_scanner_type> detector;
    dlib::deserialize(modelsConfig_["boat_detector"]) >> detector;
    return detector;
}

AdaVisionConfig::MachineLearning::Models::Models(const dlib::config_reader &config) :
        modelsConfig_(config)
{ }


AdaVisionConfig::Output::Output(const dlib::config_reader &config) :
        outputConfig_(config)
{ }

std::string AdaVisionConfig::Output::liveFeedPort() const {
    return outputConfig_["live_feed_port"];
}

std::string AdaVisionConfig::Output::dangerZonePubPort() const {
    return outputConfig_["dangerzone_pub_port"];
}

int AdaVisionConfig::Output::frameSkip() const {
    return dlib::get_option(outputConfig_, "frame_skip", 1);
}

std::string AdaVisionConfig::Output::dataDir() const {
    return outputConfig_["data_dir"];
}

std::string AdaVisionConfig::Output::logDir() const {
    return outputConfig_["log_dir"];
}
