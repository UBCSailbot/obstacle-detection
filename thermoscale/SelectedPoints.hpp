#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


class SelectedPoints {
        cv::Point* points;
        int size;

    public:
        SelectedPoints();

        int getSize();
        void add(cv::Point point);
        void setPoints(cv::Point* points, int size);
        void draw(cv::Mat* img);

    private:
        void drawSquareAroundPixel(cv::Mat* img, int orig_x, int orig_y);

};