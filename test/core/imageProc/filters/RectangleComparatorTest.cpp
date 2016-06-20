#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>
#include <imageProc/filters/RectangleComparator.h>

class RectangleComparatorTest : public testing::Test {
public:
    cv::Rect rect1 = cv::Rect(2, 2, 10, 10);
    cv::Rect rect2 = cv::Rect(2, 2, 8, 8);
    cv::Rect rect3 = cv::Rect(30, 2, 8, 8);
    cv::Rect rect4 = cv::Rect(0, 0, 20, 20);
    cv::Rect rect5 = cv::Rect(18, 18, 20, 20);

};

TEST_F(RectangleComparatorTest, filterRectanglesWithMoreInFirstVector) {
    //Setup
    std::vector<cv::Rect> rects1;
    rects1.push_back(rect1);
    std::vector<cv::Rect> rects2;
    rects2.push_back(rect2);
    rects2.push_back(rect3);

    std::vector<cv::Rect> filteredRects1 = RectangleComparator::getCommonRectangles(rects1, rects2);

    EXPECT_TRUE(filteredRects1.size() == 1);
    EXPECT_TRUE(filteredRects1[0] == cv::Rect(2, 2, 10, 10));
}

TEST_F(RectangleComparatorTest, filterRectanglesWithMoreInSecondVector) {
    //Setup
    std::vector<cv::Rect> rects1;
    rects1.push_back(rect2);
    rects1.push_back(rect3);
    std::vector<cv::Rect> rects2;
    rects2.push_back(rect1);
    //Execute
    std::vector<cv::Rect> filteredRects1 = RectangleComparator::getCommonRectangles(rects1, rects2);
    //Verify
    EXPECT_TRUE(filteredRects1.size() == 1);
    EXPECT_TRUE(filteredRects1[0] == cv::Rect(2, 2, 10, 10));
}

TEST_F(RectangleComparatorTest, filterAll) {
    //Setup
    std::vector<cv::Rect> rects1;
    rects1.push_back(rect2);
    std::vector<cv::Rect> rects2;
    rects2.push_back(rect3);
    //Execute
    std::vector<cv::Rect> filteredRects1 = RectangleComparator::getCommonRectangles(rects1, rects2);
    //Verify
    EXPECT_TRUE(filteredRects1.size() == 0);
}

TEST_F(RectangleComparatorTest, bigBoxTinyBox) {
    //Setup
    std::vector<cv::Rect> rects1;
    rects1.push_back(rect2);
    std::vector<cv::Rect> rects2;
    rects2.push_back(rect4);
    //Execute
    std::vector<cv::Rect> filteredRects1 = RectangleComparator::getCommonRectangles(rects1, rects2);
    //Verify
    EXPECT_TRUE(filteredRects1.size() == 0);
}

TEST_F(RectangleComparatorTest, justTheTip) {
    //Setup
    std::vector<cv::Rect> rects1;
    rects1.push_back(rect4);
    std::vector<cv::Rect> rects2;
    rects2.push_back(rect5);
    //Execute
    std::vector<cv::Rect> filteredRects1 = RectangleComparator::getCommonRectangles(rects1, rects2);
    //Verify
    EXPECT_TRUE(filteredRects1.size() == 0);
}


