#include "ResourcesTest.h"

TEST(ResourcesTest, testImuConfigPath) {
    std::string imuConfigFilePath = Resources::getConfigFilePath("RTIMULib.ini");

    int fd = open(imuConfigFilePath.c_str(), O_RDONLY);

    if (fd >= 0) {
        close(fd);
    }

    EXPECT_GT(fd, 0);
}
