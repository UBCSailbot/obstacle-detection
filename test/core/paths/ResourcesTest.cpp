#include "ResourcesTest.h"

TEST(ResourcesTest, testImuConfigPath) {
    std::string imuConfigFilePath = Resources::getConfigFilePath("RTIMULib.ini");

    int fd = open(imuConfigFilePath.c_str(), O_RDONLY);

    // clean-up before end of test
    if (fd >= 0) {
        close(fd);
    }

    EXPECT_GT(fd, 0);
}

TEST(ResourcesTest, testConfigDirExists) {
    std::string configDir = Resources::getConfigDir();

    DIR* dir = opendir(configDir.c_str());
    // clean-up before end of test
    free(dir);

    EXPECT_TRUE(dir != NULL);
}
