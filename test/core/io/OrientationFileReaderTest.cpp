//
// Created by paul on 16/06/15.
//

#include "OrientationFileReaderTest.h"

TEST_F(HorizonFileReaderTest, firstFewLines) {

    std::string fileName = Resources::getResourcePath("imu/sailboatTurnaround.txt");
    OrientationFileReader reader(fileName);

    EXPECT_EQ(Orientation(-0.0132741, -0.0693999, -2.67356), reader.next());
    EXPECT_EQ(Orientation(-0.0122837, -0.0683239, -2.67513), reader.next());

}

HorizonFileReaderTest::HorizonFileReaderTest() {

}