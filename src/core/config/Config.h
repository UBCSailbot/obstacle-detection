#ifndef OBSTACLE_DETECTION_CONFIG_H
#define OBSTACLE_DETECTION_CONFIG_H

#include <dlib/config_reader.h>
#include <imageProc/dlib/DLibProcessor.h>
#include <io/BoatDataStream.h>
#include <features/SunImage.h>
#include "config/ConfigMacros.h"

namespace od {

/**
 * An object for neatly interfacing with a config file for programs related
 * to obstacle detection.
 *
 * Has the following features:
 *   1) fields are loaded only as they are called, so you don't get
 *      penalized for omitting fields that you don't use
 *   2) each field is scoped, so that the nested structure of the object
 *      reflects the nested structure of the config file
 *   3) is completely stateless
 *   4) eliminates significant amounts of boilerplate code through a clever
 *      (if I may say so myself) yet simple series of macros that take care
 *      of a bunch of code generation. See documentation in ConfigMacros.h.
 *
 * NOTE: A consequence of the statelessness is that every time a function
 *  is called to retrieve a field, all the work done in that function is
 *  repeated.
 */
class Config {

public:
    Config(std::string configFilePath) : config_(configFilePath) {}

    /**
     * Settings for communications between processes
     */
    START_CONFIG_SECTION(comms)
        ADD_REQUIRED_STRING_FIELD(camera_server_ip)
        ADD_REQUIRED_STRING_FIELD(camera_server_pub_port)
        ADD_REQUIRED_STRING_FIELD(live_feed_pub_port)
        ADD_REQUIRED_STRING_FIELD(dangerzone_channel)
        ADD_REQUIRED_STRING_FIELD(current_data_channel)
    END_CONFIG_SECTION(comms)

    /**
     * Settings for detecting objects using computer vision; shared across multiple programs
     */
    START_CONFIG_SECTION(perception)

        START_CONFIG_SECTION(sun_detection)
            ADD_DEFAULT_FIELD(sun_pixel_threshold, SunImage::DEFAULT_MIN_SUN_PIXEL_VALUE)
            ADD_DEFAULT_FIELD(glint_pixel_threshold, SunImage::DEFAULT_MIN_GLINT_PIXEL_VALUE)
        END_CONFIG_SECTION(sun_detection)

        typedef dlib::object_detector<DLibProcessor::image_scanner_type> ObjectDetectorType;

        START_CONFIG_SECTION(boat_detection)
            START_CONFIG_SECTION(models)
                std::vector<perception_config::ObjectDetectorType> all() const;
            END_CONFIG_SECTION(models)
        END_CONFIG_SECTION(boat_detection)

    END_CONFIG_SECTION(perception)

    /**
     * AdaVision settings
     */
    START_CONFIG_SECTION(adavision)
        ADD_DEFAULT_FIELD(debug, true)

        enum ImageSource {
            FILE,
            NETWORK,
            UNINITIALIZED
        };

        ADD_COMPLEX_FIELD(image_source, ImageSource)

        START_CONFIG_SECTION(file_input)
            ADD_REQUIRED_STRING_FIELD(input_frame_dir)
            ADD_DEFAULT_FIELD(double_up, true)
        END_CONFIG_SECTION(file_input)

        START_CONFIG_SECTION(imu)

            enum ImuMode {
                STUB,
                REAL,
                FILE
            };

            ADD_COMPLEX_FIELD(mode, ImuMode)
        END_CONFIG_SECTION(imu)

        START_CONFIG_SECTION(current_data)

            enum CurrentDataMode {
                STUB,
                REAL
            };

            ADD_COMPLEX_FIELD(mode, CurrentDataMode)
        END_CONFIG_SECTION(current_data)

        START_CONFIG_SECTION(output)
            ADD_DEFAULT_FIELD(frame_skip, 1)
            ADD_REQUIRED_STRING_FIELD(data_dir)
            ADD_REQUIRED_STRING_FIELD(log_dir)
        END_CONFIG_SECTION(output)

    END_CONFIG_SECTION(adavision)

    /**
     * Camera enclosure settings
     */
    START_CONFIG_SECTION(camera_enclosure)

        ADD_DEFAULT_FIELD(debug, true)

        enum ImageSource {
            FILE,
            LEPTON,
            UNINITIALIZED
        };

        ADD_COMPLEX_FIELD(image_source, ImageSource)

        /**
         * Lepton settings
         */
        START_CONFIG_SECTION(lepton)
            ADD_DEFAULT_FIELD(use_lepton0, true)
            ADD_DEFAULT_FIELD(use_lepton1, true)

            ADD_DEFAULT_FIELD(status_check_interval_s, (unsigned int) 5)

            START_CONFIG_SECTION(ffc_behavior)
                ADD_DEFAULT_FIELD(ffc_auto, true)
                ADD_DEFAULT_FIELD(ffc_interval_s, 60)
            END_CONFIG_SECTION(ffc_behavior)

            START_CONFIG_SECTION(failure_behavior)
                ADD_DEFAULT_FIELD(reset_time_millis, (unsigned int) 5000)
            END_CONFIG_SECTION(failure_behavior)

            START_CONFIG_SECTION(sun_behavior)
                ADD_DEFAULT_FIELD(sun_duty_cycle_percent, (unsigned int) 50)
            END_CONFIG_SECTION(sun_behavior)

        END_CONFIG_SECTION(lepton)

        START_CONFIG_SECTION(file_input)
            ADD_REQUIRED_STRING_FIELD(input_frame_dir)
        END_CONFIG_SECTION(file_input)

    END_CONFIG_SECTION(camera_enclosure)

private:
    dlib::config_reader config_;
};

}


#endif //OBSTACLE_DETECTION_CONFIG_H
