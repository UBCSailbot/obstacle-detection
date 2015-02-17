#include <ctime>

#include "Obstacle.h"


Obstacle::Obstacle(float init_pos) {
	// set birth time to current time; TODO test this
	birth_time = time(NULL);
	cur_position = init_pos;

}

Obstacle::~Obstacle() {
	// TODO Auto-generated destructor stub
}

