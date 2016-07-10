#include <gtest/gtest.h>
#include <io/BearingConverter.h>

class BearingConverterTest : public ::testing::Test {

};

TEST_F(BearingConverterTest, nullTest) {
    double relative = 0.0;
    double heading = 0.0;

    double absoluteBearing = BearingConverter::relativeToAbsoluteBearing(relative, heading);

    EXPECT_EQ(absoluteBearing, 0);
}

TEST_F(BearingConverterTest, starboardTest1) {
    double relative = 20.0;
    double heading = 90.0;

    double absoluteBearing = BearingConverter::relativeToAbsoluteBearing(relative, heading);

    EXPECT_EQ(absoluteBearing, 110);
}

TEST_F(BearingConverterTest, starboardTest2) {
    double relative = -20.0;
    double heading = 90.0;

    double absoluteBearing = BearingConverter::relativeToAbsoluteBearing(relative, heading);

    EXPECT_EQ(absoluteBearing, 70);
}

TEST_F(BearingConverterTest, starboardTest3) {
    double relative = -20.0;
    double heading = 10.0;

    double absoluteBearing = BearingConverter::relativeToAbsoluteBearing(relative, heading);

    EXPECT_EQ(absoluteBearing, -10);
}


TEST_F(BearingConverterTest, starboardTest4) {
    double relative = 20.0;
    double heading = 170.0;

    double absoluteBearing = BearingConverter::relativeToAbsoluteBearing(relative, heading);

    EXPECT_EQ(absoluteBearing, -170);
}

TEST_F(BearingConverterTest, portTest1) {
    double relative = -20.0;
    double heading = -90.0;

    double absoluteBearing = BearingConverter::relativeToAbsoluteBearing(relative, heading);

    EXPECT_EQ(absoluteBearing, -110);
}

TEST_F(BearingConverterTest, portTest2) {
    double relative = +20.0;
    double heading = -90.0;

    double absoluteBearing = BearingConverter::relativeToAbsoluteBearing(relative, heading);

    EXPECT_EQ(absoluteBearing, -70);
}

TEST_F(BearingConverterTest, portTest3) {
    double relative = 20.0;
    double heading = -10.0;

    double absoluteBearing = BearingConverter::relativeToAbsoluteBearing(relative, heading);

    EXPECT_EQ(absoluteBearing, 10);
}

TEST_F(BearingConverterTest, portTest4) {
    double relative = -20.0;
    double heading = -170.0;

    double absoluteBearing = BearingConverter::relativeToAbsoluteBearing(relative, heading);

    EXPECT_EQ(absoluteBearing, 170);
}


TEST_F(BearingConverterTest, nullTest2) {
    double relative = -180.0;
    double heading = 0;

    double absoluteBearing = BearingConverter::relativeToAbsoluteBearing(relative, heading);

    EXPECT_EQ(absoluteBearing, 180);
}

TEST_F(BearingConverterTest, nullTest3) {
    double relative = 180.0;
    double heading = 0;

    double absoluteBearing = BearingConverter::relativeToAbsoluteBearing(relative, heading);

    EXPECT_EQ(absoluteBearing, 180);
}

TEST_F(BearingConverterTest, starboardTest5) {
    double relative = 100;
    double heading = 90;

    double absoluteBearing = BearingConverter::relativeToAbsoluteBearing(relative, heading);

    EXPECT_EQ(absoluteBearing, -170);
}