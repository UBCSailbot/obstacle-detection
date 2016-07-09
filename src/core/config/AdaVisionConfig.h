#ifndef OBSTACLE_DETECTION_ADAVISIONCONFIGREADER_H
#define OBSTACLE_DETECTION_ADAVISIONCONFIGREADER_H


#include <string>
#include <dlib/config_reader.h>
#include <dlib/image_processing/object_detector.h>

#include "imageProc/dlib/DLibProcessor.h"

/**
 * An object for neatly interfacing with a config file for AdaVision.
 *
 * Has the following features:
 *   1) fields are loaded only as they are called, so you don't get
 *      penalized for omitting fields that you don't use
 *   2) each field is scoped, so that the nested structure of the object
 *      reflects the nested structure of the config file
 *   3) is completely stateless
 *
 * NOTE: A consequence of the statelessness is that every time a function
 *  is called to retrieve a field, all the work done in that function is
 *  repeated.
 */
class
AdaVisionConfig {

public:
    AdaVisionConfig(const std::string &configFilePath);

    struct Global {

        Global(const dlib::config_reader &config);

        bool debug() const;

    private:
        const dlib::config_reader &globalConfig_;
    };

    struct Imu {
        enum Mode {
            FILE,
            STUB,
            REAL
        };

        Imu(const dlib::config_reader &config);

        Mode mode() const;

    private:
        const dlib::config_reader &imuConfig_;
    };

    struct ImageSource {
        enum Source {
            FILE,
            NETWORK,
            UNINITIALIZED
        };

        ImageSource(const dlib::config_reader &config);

        struct File {
            File(const dlib::config_reader &config);

            std::string inputDir() const;

            bool doubleUp() const;

        private:
            const dlib::config_reader &fileConfig_;
        };

        struct Network {
            Network(const dlib::config_reader &config);

            std::string imagePubIP() const;

            std::string imagePubPort() const;

        private:
            const dlib::config_reader &networkConfig_;;
        };

        Source source() const;

        File file() const;

        Network network() const;

    private:
        const dlib::config_reader &imageSourceConfig_;
    };

    struct Output {
        Output(const dlib::config_reader &config);

        std::string dangerZonePubPort() const;

        std::string liveFeedPort() const;

        int frameSkip() const;

        std::string dataDir() const;

        std::string logDir() const;

    private:
        const dlib::config_reader &outputConfig_;
    };

    struct CurrentData {

        enum Mode {
            STUB,
            REAL
        };

        CurrentData(const dlib::config_reader &config);

        Mode mode() const;

        std::string zmqAddress() const;

        int mockHeading() const;

    private:
        const dlib::config_reader &_currentDataConfig;
    };

    struct MachineLearning {
        typedef dlib::object_detector<DLibProcessor::image_scanner_type> ObjectDetectorType;

        MachineLearning(const dlib::config_reader &config);

        struct Models {
            Models(const dlib::config_reader &config);

            std::vector<ObjectDetectorType> all() const;

            ObjectDetectorType boatDetector() const;

        private:
            const dlib::config_reader &modelsConfig_;
        };

        Models models() const;

    private:
        const dlib::config_reader &mlConfig_;
    };

    Global global() const;

    Imu imu() const;

    CurrentData currentData() const;

    ImageSource imageSource() const;

    Output output() const;

    MachineLearning machineLearning() const;

private:
    dlib::config_reader config_;

};


#endif //OBSTACLE_DETECTION_ADAVISIONCONFIGREADER_H
