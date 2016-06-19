#include <gtest/gtest.h>
#include <config/AdaVisionConfig.h>
#include <paths/Resources.h>

/**
 * A test fixture class that just loads the canonical AdaVision config.
 * By canonical, we just mean the sample config that contains examples
 * of all the fields that a config for AdaVision can have.
 */
class AdaVisionConfigReaderTest : public testing::Test {

public:
    AdaVisionConfigReaderTest() :
            config(Resources::getConfigFilePath("adavision-config-example.txt"))
    {}

protected:
    AdaVisionConfig config;
};

/**
 * This unit test doesn't really care about the values that are
 * loaded, so long as they are loaded without error.
 */
TEST_F(AdaVisionConfigReaderTest, loadAllValues) {
    config.global().debug();
    config.imageSource().source();
    config.imageSource().file().doubleUp();
    config.imageSource().file().inputDir();
    config.imageSource().network().imagePubIP();
    config.imageSource().network().imagePubPort();
    config.output().liveFeedPort();
    config.output().dangerZonePubPort();
    config.output().frameSkip();
    config.output().dataDir();
    config.output().logDir();
    config.machineLearning().models().all();
    config.machineLearning().models().boatDetector();
    EXPECT_TRUE(config.global().debug());

}