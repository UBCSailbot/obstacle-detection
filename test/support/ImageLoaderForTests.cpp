//
// Created by paul on 10/06/15.
//

#include "ImageLoaderForTests.h"

ImageLoaderForTests::ImageLoaderForTests() {
    _fishingBoatImg = cv::imread(Resources::getImagePath("fishingBoat01.png"), CV_LOAD_IMAGE_UNCHANGED);
    _freighterSunImg = cv::imread(Resources::getImagePath("freighterAndSun01.png"), CV_LOAD_IMAGE_UNCHANGED);
    _garbledImg = cv::imread(Resources::getImagePath("garbled01.png"), CV_LOAD_IMAGE_UNCHANGED);
}
