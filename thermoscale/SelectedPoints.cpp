#include "SelectedPoints.hpp"
#include "thermoscale.hpp"
#include <stdlib.h>
#include <iostream>

SelectedPoints::SelectedPoints() {
    size = 0;
    points = (cv::Point*) malloc( 60 * 80 * sizeof(cv::Point) );
}

void SelectedPoints::add(cv::Point point) {
    points[size] = point;
    size++;
    std::cout << "Size of sp: " << size << std::endl;
}

int SelectedPoints::getSize() {
    return size;
}

void SelectedPoints::setPoints(cv::Point* new_points, int new_size) {
    // for(int i=0; i < size; i++) {
    //     delete &(points[i]);
    // }
    free(points);
    points = new_points;
    size = new_size;
}

void SelectedPoints::draw(cv::Mat* img) {
    for (int i=0; i < size; i++)
        drawSquareAroundPixel(img, points[i].x, points[i].y);
}

void SelectedPoints::drawSquareAroundPixel(cv::Mat* img, int orig_x, int orig_y) {
    int x1 = orig_x*WIN_ZOOM_FACTOR;
    int y1 = orig_y*WIN_ZOOM_FACTOR;
    int x2 = x1 + WIN_ZOOM_FACTOR - 1;
    int y2 = y1 + WIN_ZOOM_FACTOR - 1;

    cv::line(*img, cv::Point(x1,y1), cv::Point(x2, y1), cv::Scalar(255,0,0), 1);
    cv::line(*img, cv::Point(x1,y1), cv::Point(x1, y2), cv::Scalar(255,0,0), 1);
    cv::line(*img, cv::Point(x2,y1), cv::Point(x2, y2), cv::Scalar(255,0,0), 1);
    cv::line(*img, cv::Point(x1,y2), cv::Point(x2, y2), cv::Scalar(255,0,0), 1);
}