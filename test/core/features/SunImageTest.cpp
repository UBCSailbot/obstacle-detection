#include "SunImageTest.h"

TEST(SunImageTest, FindSunPositive) {
    cv::Mat frame = cv::imread(
            Resources::getImagePath("16bit/freighterAndSun01.png"),
            CV_LOAD_IMAGE_UNCHANGED);
    Horizon h = Horizon(cv::Point2f (0, 50), cv::Point2f (LeptonCameraSpecifications.pixelWidth - 1, 50));
    SunImage sunImage = SunImage(h, frame, 9000, 0, 1);

    EXPECT_EQ(sunImage.getSunPosition(), Rect2f(36, 36, 2, 2));
}

TEST(SunImageTest, FindSunNegative) {
    cv::Mat frame = cv::imread(
            Resources::getImagePath("16bit/fishingBoat01.png"),
            CV_LOAD_IMAGE_UNCHANGED);
    Horizon h = Horizon(cv::Point2f (0, 50), cv::Point2f (LeptonCameraSpecifications.pixelWidth - 1, 50));
    SunImage sunImage = SunImage(h, frame, 9000, 0, 1);

    EXPECT_FALSE(sunImage.containsSun());
    EXPECT_EQ(sunImage.getSunPosition(), Rect2f(-1.0, -1.0, -1.0, -1.0));
}

TEST(SunImageTest, FindColumn0Pix) {
    cv::Mat frame = cv::Mat(LeptonCameraSpecifications.pixelHeight, LeptonCameraSpecifications.pixelWidth, CV_16UC1, cv::Scalar(0));
    Horizon h = Horizon(cv::Point2f (0, 0), cv::Point2f (LeptonCameraSpecifications.pixelWidth - 1, 0));
    SunImage sunImage = SunImage(h, frame, 9000, 9000, 1);

    EXPECT_EQ(sunImage.getLeftGlintMargin()->getStartPoint(), cv::Point2f(-1.0, -1.0));
    EXPECT_EQ(sunImage.getLeftGlintMargin()->getEndPoint(), cv::Point2f(-1.0, -1.0));
    EXPECT_EQ(sunImage.getRightGlintMargin()->getStartPoint(), cv::Point2f(-1.0, -1.0));
    EXPECT_EQ(sunImage.getRightGlintMargin()->getEndPoint(), cv::Point2f(-1.0, -1.0));
}

TEST(SunImageTest, FindColumnPixAboveHorizon) {
    cv::Mat frame = cv::Mat(LeptonCameraSpecifications.pixelHeight, LeptonCameraSpecifications.pixelWidth, CV_16UC1, cv::Scalar(0));
    frame.at<uint16_t>(0, 20) = 9000;
    Horizon h = Horizon(cv::Point2f (0, 40), cv::Point2f (LeptonCameraSpecifications.pixelWidth - 1, 40));
    SunImage sunImage = SunImage(h, frame, 9000, 0, 1);

    EXPECT_EQ(sunImage.getLeftGlintMargin()->getStartPoint(), cv::Point2f(20, 0));
    EXPECT_EQ(sunImage.getLeftGlintMargin()->getEndPoint(), cv::Point2f(20, 59));
    EXPECT_EQ(sunImage.getRightGlintMargin()->getStartPoint(), cv::Point2f(20, 0));
    EXPECT_EQ(sunImage.getRightGlintMargin()->getEndPoint(), cv::Point2f(20, 59));
}

TEST(SunImageTest, FindColumnPixBelowFlatHorizonWithSun) {
    cv::Mat frame = cv::Mat(LeptonCameraSpecifications.pixelHeight, LeptonCameraSpecifications.pixelWidth, CV_16UC1, cv::Scalar(0));
    frame.at<uint16_t>(0, 0) = 9000;
    frame.at<uint16_t>(52, 55) = 9000;
    frame.at<uint16_t>(57, 53) = 9000;
    Horizon h = Horizon(cv::Point2f (0, 40), cv::Point2f (LeptonCameraSpecifications.pixelWidth - 1, 40));
    SunImage sunImage = SunImage(h, frame, 9000, 9000, 1);

    EXPECT_NE(sunImage.getLeftGlintMargin()->getStartPoint(), cv::Point2f(53, 0));
    EXPECT_NE(sunImage.getLeftGlintMargin()->getEndPoint(), cv::Point2f(53, 59));
    EXPECT_NE(sunImage.getRightGlintMargin()->getStartPoint(), cv::Point2f(55, 0));
    EXPECT_NE(sunImage.getRightGlintMargin()->getEndPoint(), cv::Point2f(55, 59));
}

TEST(SunImageTest, FindColumnPixBelowFlatHorizon) {
    cv::Mat frame = cv::Mat(LeptonCameraSpecifications.pixelHeight, LeptonCameraSpecifications.pixelWidth, CV_16UC1, cv::Scalar(0));
    frame.at<uint16_t>(52, 55) = 9000;
    frame.at<uint16_t>(57, 53) = 9000;
    Horizon h = Horizon(cv::Point2f (0, 40), cv::Point2f (LeptonCameraSpecifications.pixelWidth - 1, 40));
    SunImage sunImage = SunImage(h, frame, 9000, 9000, 1);

    EXPECT_EQ(sunImage.getLeftGlintMargin()->getStartPoint(), cv::Point2f(53, 0));
    EXPECT_EQ(sunImage.getLeftGlintMargin()->getEndPoint(), cv::Point2f(53, 59));
    EXPECT_EQ(sunImage.getRightGlintMargin()->getStartPoint(), cv::Point2f(55, 0));
    EXPECT_EQ(sunImage.getRightGlintMargin()->getEndPoint(), cv::Point2f(55, 59));
}

TEST(SunImageTest, FindColumnPixBelowDiagHorizon) {
    cv::Mat frame = cv::Mat(LeptonCameraSpecifications.pixelHeight, LeptonCameraSpecifications.pixelWidth, CV_16UC1, cv::Scalar(0));
    frame.at<uint16_t>(52, 55) = 9000;
    frame.at<uint16_t>(57, 53) = 9000;
    Horizon h = Horizon(cv::Point2f (0, 30), cv::Point2f (LeptonCameraSpecifications.pixelWidth - 1, 50));
    SunImage sunImage = SunImage(h, frame, 9000, 9000, 1);

    EXPECT_FLOAT_EQ(sunImage.getLeftGlintMargin()->getStartPoint().x,  67.43037975);
    EXPECT_FLOAT_EQ(sunImage.getLeftGlintMargin()->getEndPoint().x,  52.49367089);
    EXPECT_FLOAT_EQ(sunImage.getRightGlintMargin()->getStartPoint().x,  68.16455696);
    EXPECT_FLOAT_EQ(sunImage.getRightGlintMargin()->getEndPoint().x,  53.2278481);
}

TEST(SunImageTest, MeanVariance0Pix) {
    cv::Mat zeros = cv::Mat(LeptonCameraSpecifications.pixelHeight, LeptonCameraSpecifications.pixelWidth, CV_16UC1, cv::Scalar(0));
    Horizon h = Horizon(cv::Point2f (0, 0), cv::Point2f (LeptonCameraSpecifications.pixelWidth - 1, 0));
    SunImage sunImage = SunImage(h, zeros, 9000, 0, 1);

    sunImage.findMeanVariance();
    EXPECT_EQ(sunImage.getMean(), -1);
    EXPECT_EQ(sunImage.getVariance(), -1);
}

TEST(SunImageTest, MeanVarianceMinSunPixelValue) {
    cv::Mat zeros = cv::Mat(LeptonCameraSpecifications.pixelHeight, LeptonCameraSpecifications.pixelWidth, CV_16UC1, cv::Scalar(0));
    zeros.at<uint16_t>(20, 20) = 8999;
    Horizon h = Horizon(cv::Point2f (0, 0), cv::Point2f (LeptonCameraSpecifications.pixelWidth - 1, 0));
    SunImage sunImage = SunImage(h, zeros, 9000, 0, 1);

    sunImage.findMeanVariance();
    EXPECT_EQ(sunImage.getMean(), -1);
    EXPECT_EQ(sunImage.getVariance(), -1);
}

TEST(SunImageTest, MeanVariance1PixFlatPointFlatHorizon) {
    cv::Mat zeros = cv::Mat(LeptonCameraSpecifications.pixelHeight, LeptonCameraSpecifications.pixelWidth, CV_16UC1, cv::Scalar(0));
    zeros.at<uint16_t>(0, 20) = 9000;
    Horizon h = Horizon(cv::Point2f (0, 0), cv::Point2f (LeptonCameraSpecifications.pixelWidth - 1, 0));
    SunImage sunImage = SunImage(h, zeros, 9000, 0, 1);

    sunImage.findMeanVariance();
    EXPECT_EQ(sunImage.getMean(), 20);
    EXPECT_EQ(sunImage.getVariance(), 0);
}

TEST(SunImageTest, MeanVariance1PixDiagPointFlatHorizon) {
    cv::Mat zeros = cv::Mat(LeptonCameraSpecifications.pixelHeight, LeptonCameraSpecifications.pixelWidth, CV_16UC1, cv::Scalar(0));
    zeros.at<uint16_t>(20, 20) = 9000;
    Horizon h = Horizon(cv::Point2f (0, 0), cv::Point2f (LeptonCameraSpecifications.pixelWidth - 1, 0));
    SunImage sunImage = SunImage(h, zeros, 9000, 0, 1);

    sunImage.findMeanVariance();
    EXPECT_EQ(sunImage.getMean(), 20);
    EXPECT_EQ(sunImage.getVariance(), 0);
}

TEST(SunImageTest, MeanVariance1PixFlatPointDiagHorizon) {
    cv::Mat zeros = cv::Mat(LeptonCameraSpecifications.pixelHeight, LeptonCameraSpecifications.pixelWidth, CV_16UC1, cv::Scalar(0));
    zeros.at<uint16_t>(0, 20) = 9000;
    Horizon h = Horizon(cv::Point2f (0, 0), cv::Point2f (LeptonCameraSpecifications.pixelWidth - 1, 59));
    SunImage sunImage = SunImage(h, zeros, 9000, 0, 1);

    sunImage.findMeanVariance();
    EXPECT_FLOAT_EQ(sunImage.getMean(), 20*cos(atan(59.0/79.0)));
    EXPECT_EQ(sunImage.getVariance(), 0);
}

TEST(SunImageTest, MeanVariance1PixFlatPointDiagHorizonWithOffSet) {
    cv::Mat zeros = cv::Mat(LeptonCameraSpecifications.pixelHeight, LeptonCameraSpecifications.pixelWidth, CV_16UC1, cv::Scalar(0));
    zeros.at<uint16_t>(0, 20) = 9000;
    Horizon h = Horizon(cv::Point2f (0, 59), cv::Point2f (LeptonCameraSpecifications.pixelWidth - 1, 0));
    SunImage sunImage = SunImage(h, zeros, 9000, 0, 1);

    sunImage.findMeanVariance();
    EXPECT_FLOAT_EQ(sunImage.getMean(), pow(pow(20, 2) + pow(59, 2), 0.5)*cos(atan(59.0/20.0) - atan(59.0/79.0)));
    EXPECT_EQ(sunImage.getVariance(), 0);
}

TEST(SunImageTest, HorizonOutsideFrame) {
    // TODO: Implement this test.
}

TEST(SunImageTest, GetDelimsNoSunPixels) {
    // TODO: Implement this test.
}
