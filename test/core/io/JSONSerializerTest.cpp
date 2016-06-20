#include <dlib/geometry/rectangle.h>
#include <io/JSONSerializer.h>
#include "JSONSerializerTest.h"

TEST_F(JSONSerializerTest, JSONTest) {

    std::vector<cv::Rect> rectangles;
    cv::Rect rect1(2, 2, 5, 5);
    cv::Rect rect2(1, 2, 5, 4);
    rectangles.push_back(rect1);
    rectangles.push_back(rect2);
    std::string img = "asdf";

    std::string expected = "{\n"
            "\t\"boxes\" : \n"
            "\t[\n"
            "\t\t{\n"
            "\t\t\t\"h\" : 5,\n"
            "\t\t\t\"w\" : 5,\n"
            "\t\t\t\"x\" : 2,\n"
            "\t\t\t\"y\" : 2\n"
            "\t\t},\n"
            "\t\t{\n"
            "\t\t\t\"h\" : 4,\n"
            "\t\t\t\"w\" : 5,\n"
            "\t\t\t\"x\" : 1,\n"
            "\t\t\t\"y\" : 2\n"
            "\t\t}\n"
            "\t],\n"
            "\t\"image\" : \"asdf\",\n"
            "\t\"imageType\" : \"8Bit\"\n"
            "}";

    EXPECT_EQ(expected, JSONSerializer::makeJSON(img, rectangles, IMAGE8BIT));
}

JSONSerializerTest::JSONSerializerTest() {

}

TEST_F(JSONSerializerTest, JSONcppLibIntegration) {
    // This line will compile and run only if jsoncpp
    //  has been correctly integrated into the project.
    Json::Value root;
}