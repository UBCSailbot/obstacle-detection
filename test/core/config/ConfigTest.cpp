#include <gtest/gtest.h>
#include <config/Config.h>
#include <paths/Resources.h>
#include <config/BadConfigException.h>

/**
 * A test fixture class that just loads the canonical obstacle detection config file.
 * By canonical, we just mean the sample config that contains examples
 * of all the fields that a config for obstacle detection can have.
 */
class ConfigTest : public testing::Test {

public:
    ConfigTest() :
            masterExampleConfig_(Resources::getConfigFilePath("master-example.config")),
            productionConfig_(Resources::getConfigFilePath("production.config"))
    {}

protected:
    od::Config masterExampleConfig_;
    od::Config productionConfig_;

    static void testProductionFields(const od::Config &config) {

        // Config fields for communication between processes
        const auto &commsConfig = config.comms();
        commsConfig.camera_server_ip();
        commsConfig.dangerzone_channel();
        commsConfig.live_feed_pub_port();
        commsConfig.current_data_channel();

        // Config fields for detecting stuff
        const auto &perceptionConfig = config.perception();
        perceptionConfig.boat_detection().models().all();
        perceptionConfig.boat_detection().models().boat_detector();
        perceptionConfig.sun_detection().sun_pixel_threshold();

        // AdaVision config fields
        const auto &adaVisionConfig = config.adavision();
        adaVisionConfig.debug();
        adaVisionConfig.image_source();
        EXPECT_EQ(od::Config::adavision_config::imu_config::REAL,
                  adaVisionConfig.imu().mode());
        EXPECT_EQ(od::Config::adavision_config::current_data_config::REAL,
                  adaVisionConfig.current_data().mode());
        adaVisionConfig.output().frame_skip();
        adaVisionConfig.output().data_dir();

        // Camera enclosure config fields
        const auto &enclosureConfig = config.camera_enclosure();
        enclosureConfig.debug();
        enclosureConfig.image_source();

        // Lepton fields
        const auto &leptonConfig = config.camera_enclosure().lepton();
        leptonConfig.status_check_interval_s();
        leptonConfig.failure_behavior().reset_time_millis();
        leptonConfig.ffc_behavior().ffc_auto();
        leptonConfig.ffc_behavior().ffc_interval_s();
        leptonConfig.sun_behavior().sun_duty_cycle_percent();
        leptonConfig.use_lepton0();
        leptonConfig.use_lepton1();
    }

    static void testNonProductionFields(const od::Config &config) {
        const auto &adaVisionConfig = config.adavision();
        adaVisionConfig.file_input().double_up();
        adaVisionConfig.file_input().input_frame_dir();
        adaVisionConfig.output().log_dir();

        const auto &enclosureConfig = config.camera_enclosure();
        enclosureConfig.file_input().input_frame_dir();
    }
};

TEST_F(ConfigTest, productionConfigLoads) {
    // Ensure that all the fields in the production config file load properly
    testProductionFields(productionConfig_);
}

TEST_F(ConfigTest, masterExampleConfigLoads) {
    // Ensure that all the fields in the master example config file load properly
    testProductionFields(masterExampleConfig_);
    testNonProductionFields(masterExampleConfig_);
}

TEST_F(ConfigTest, defaultValues) {
    // Make sure default values of config fields that have them are properly overridden
    EXPECT_EQ(42,
              masterExampleConfig_.camera_enclosure().lepton().sun_behavior().sun_duty_cycle_percent());
}

TEST_F(ConfigTest, imageSources) {
    // Make sure image sources are properly initialized from file
    EXPECT_EQ(od::Config::adavision_config::ImageSource::FILE,
              masterExampleConfig_.adavision().image_source());
    EXPECT_EQ(od::Config::camera_enclosure_config::ImageSource::LEPTON,
              masterExampleConfig_.camera_enclosure().image_source());
}

TEST_F(ConfigTest, failOnBadImageSource) {
    // If the image source is invalid, make sure the proper exception is thrown
    dlib::config_reader reader;
    std::istringstream mockConfig("image_source = asdfsdf");
    reader.load_from(mockConfig);

    od::Config::adavision_config adaVisionConfig(reader);
    EXPECT_THROW(adaVisionConfig.image_source(), BadConfigException);

    od::Config::camera_enclosure_config enclosureConfig(reader);
    EXPECT_THROW(enclosureConfig.image_source(), BadConfigException);
}
