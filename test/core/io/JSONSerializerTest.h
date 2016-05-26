#ifndef OBSTACLE_AVOIDANCE_JSONSERIALIZERTEST_H
#define OBSTACLE_AVOIDANCE_JSONSERIALIZERTEST_H

#include <gtest/gtest.h>
#include <json/json.h>

#include <vector>
#include <dlib/data_io.h>
#include <dlib/opencv.h>
#include "io/JSONSerializer.h"


class JSONSerializerTest : public ::testing::Test {

protected:

    JSONSerializerTest();

};


#endif //OBSTACLE_AVOIDANCE_JSONSERIALIZERTEST_H
