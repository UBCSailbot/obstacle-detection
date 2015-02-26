#include "16bitgray.h"

#define IMG_ROWS 600
#define IMG_COLS 800

uint16_t raw_img[IMG_ROWS][IMG_COLS];

int window_num = 1;

cv::Mat generate_16bit_img() {

	cv::Mat img(IMG_ROWS, IMG_COLS, CV_16UC1);

	for (int i = 0; i < IMG_ROWS; i++) {
		for (int j=0; j < IMG_COLS; j++) {
			img.at<uint16_t>(i,j) = (i + j) * 50;
		}
	}

//	cv::Mat img(IMG_ROWS, IMG_COLS, CV_16UC1, &(raw_img[0][0]));
	return img;

}

void save_16bit_img(const std::string& out_path, const cv::Mat& img, int compress_lvl) {

	std::vector<int> compress_params;
	compress_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compress_params.push_back(compress_lvl);

	cv::imwrite(out_path, img);

}

void show_16bit_img(const cv::Mat& img) {

	std::ostringstream stringStream;
	stringStream << "window" << window_num;
	std::string win_name = stringStream.str();

	cv::imshow(win_name, img);
	cv::waitKey(0);
	window_num++;

}

cv::Mat load_16bit_img(const std::string& filename) {

	cv::Mat img = cv::imread(filename, CV_LOAD_IMAGE_UNCHANGED);
	return img;

}

int max_pixel_val(const cv::Mat& img) {

	int max_val = 0;

	for (int i=0; i < img.rows; i++) {
		for (int j=0; j < img.cols; j++) {
			int cur_val = img.at<uint16_t>(i,j);
			if (cur_val > max_val)
				max_val = cur_val;
		}
	}

	return max_val;

}

void test_16bitgray() {

	cv::Mat img = generate_16bit_img();
	show_16bit_img(img);
	save_16bit_img("out.png", img, 0);
	if(img.at<uint16_t>(450,450) == (450 + 450) * 50)
		std::cout << "Writing original 16-bit image to file." << std::endl;

	std::cout << "Max val in original 16-bit image is " <<
				max_pixel_val(img) << std::endl;

	cv::Mat img2 = load_16bit_img("out.png");
	if(img2.at<uint16_t>(450,450) == (450 + 450) * 50)
		std::cout << "Showing re-loaded 16-bit image." << std::endl;
	show_16bit_img(img2);

	std::cout << "Max val in re-loaded 16-bit image is " <<
			max_pixel_val(img2) << std::endl;
}
