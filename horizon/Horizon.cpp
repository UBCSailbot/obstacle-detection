#include "Horizon.h"

/*
Determine the number of pixels by which the image of the horizon is shifted.
IN:
angle_radians: pitch (forward/backward) angle of boat. Backward pitch (looking up, horizon at bottom) is positive.

OUT:
RETURN:
pixel_shift: 0 when horizon centred, +height/2 when horizon at top, -height/2 at bottom.
May exceed magnitude height/2 for large angles.
*/
double Horizon::pitchHorizonPixelShift(double angle){
	return -(double) angle / ((double) VIEWPORT_FOV_DEGREES_VERTICAL * PI / 180.0) * (double) VIEWPORT_HEIGHT_PIX;
}

/*
Determine the number of pixels by which the image of the horizon is differentially shifted.
When the boat is rolled left (positive tilt), the horizon appears higher in the image on the left side than on the right.
IN:
angle_radians: roll (left/right) angle of boat. Left roll (horizon high on left side) is positive.

OUT:
RETURN:
pixel_shift: 0 when horizon centred, +height/2 when horizon from top left to bottom right.
May exceed magnitude height/2 for large angles.
*/
double Horizon::rollHorizonPixelShift(double angle) {
	return tan(angle) * (double) VIEWPORT_WIDTH_PIX / 2.0;
}