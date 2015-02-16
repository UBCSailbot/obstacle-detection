#include <opencv2/opencv.hpp>

#include "sensors/lepton.hpp"
#include "img_proc/horizon_finder.h"
#include "img_proc/HorizonFoundImg.h"
#include "Obstacle.h"

#include "detect_obstacles.h"


/**
 * Returns a non-null obstacle object if an obstacle is detected ahead.
 */
Obstacle* detect_obstacles(cv::Mat* frame, float roll_angle) {

	HorizonFoundImg* img = findHorizon(*frame, roll_angle);
	(void)img;

	// scan below the horizon for obstacles

	// scan at the horizon for obstacles

	// if obstacles are detected, somehow relay information on obstacle position to higher level.
	// This will probably need to be implemented through some sort of object.

	return NULL;

}
