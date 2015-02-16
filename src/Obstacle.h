#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include <ctime>
#include <vector>

class Obstacle {
public:
	Obstacle(float init_pos);
	~Obstacle();

	float getPosition();

	// functionality to keep track of Obstacle's progress

private:
	float cur_position;
	time_t birth_time;
	std::vector<float> position_history;

};

#endif /* OBSTACLE_H_ */
