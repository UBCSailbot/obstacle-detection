#include "DisplayImage.h"
#include "16bitgray.h"
#include <unistd.h>
#include "img_proc/horizon_finder.h"

int main() {

	std::string img_path = "out.png";
	cv::Mat img = cv::imread(img_path, -1);

	findHorizon(img, 30);
	findHorizon(img, -30);
	findHorizon(img, 45);
	findHorizon(img, -45);
	findHorizon(img, -181);
	findHorizon(img, 190);
	findHorizon(img, -330);
	findHorizon(img, 330);

	return 0;

}
