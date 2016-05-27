#include <dlib/geometry/rectangle.h>
#include <io/JSONSerializer.h>
#include "JSONSerializerTest.h"

TEST_F(JSONSerializerTest, JSONTest) {

    std::vector<dlib::rectangle> dets;
    dlib::rectangle rect1(2, 2, 5, 5);
    dlib::rectangle rect2(1, 2, 5, 4);
    dets.push_back(rect1);
    dets.push_back(rect2);
    std::string img = "asdf";

    std::string expected = "{\n"
            "\t\"boxes\" : \n"
            "\t[\n"
            "\t\t{\n"
            "\t\t\t\"h\" : 4,\n"
            "\t\t\t\"w\" : 4,\n"
            "\t\t\t\"x\" : 2,\n"
            "\t\t\t\"y\" : 2\n"
            "\t\t},\n"
            "\t\t{\n"
            "\t\t\t\"h\" : 3,\n"
            "\t\t\t\"w\" : 5,\n"
            "\t\t\t\"x\" : 1,\n"
            "\t\t\t\"y\" : 2\n"
            "\t\t}\n"
            "\t],\n"
            "\t\"image\" : \"asdf\"\n"
            "}";

    EXPECT_EQ(expected, makeJSON(img, dets));
}

JSONSerializerTest::JSONSerializerTest() {

}

TEST_F(JSONSerializerTest, JSONcppLibIntegration) {
    // This line will compile and run only if jsoncpp
    //  has been correctly integrated into the project.
    Json::Value root;
}