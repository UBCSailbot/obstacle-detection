//
// Created by paul on 09/05/15.
//

#include <gtest/gtest.h>

int main(int argc, char **argv) {

    ::testing::GTEST_FLAG(death_test_style) = "threadsafe";

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
