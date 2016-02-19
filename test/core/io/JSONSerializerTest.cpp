#include <dlib/geometry/rectangle.h>
#include <io/JSONSerializer.h>
#include "JSONSerializerTest.h"

TEST_F(JSONSerializerTest, JSONTest) {

    std::vector<dlib::rectangle> dets;
    dlib::rectangle rect1(2,2,5,5);
    dlib::rectangle rect2(1,2,5,4);
    dets.push_back(rect1);
    dets.push_back(rect2);
    std::string img ="asdf" ;

    std::string expected = "{image:\"asdf\", boxes:[{x:2,y:2,w:4,h:4},{x:1,y:2,w:5,h:3}]}";

    EXPECT_EQ(expected,makeJSON(img,dets));
}

JSONSerializerTest::JSONSerializerTest() {

}
