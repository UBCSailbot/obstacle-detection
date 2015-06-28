//
// Created by paul on 16/06/15.
//

#include "HorizonFileReaderTest.h"

TEST_F(HorizonFileReaderTest, firstFewLines) {

    std::string fileName = Resources::getResourcePath("imu/sailboatTurnaround.txt");
    HorizonFileReader reader(fileName);

    EXPECT_EQ(Horizon(-0.0132741, -0.0693999), reader.next());
    EXPECT_EQ(Horizon(-0.0122837, -0.0683239), reader.next());

}

HorizonFileReaderTest::HorizonFileReaderTest() {

}