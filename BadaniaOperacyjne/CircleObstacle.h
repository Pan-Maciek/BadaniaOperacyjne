#pragma once
#include "Obstacle.h"
class CircleObstacle :public Obstacle {
public:
	double radius;
	CircleObstacle(glm::vec2 pos, double radius) { this->radius = radius; this->pos = pos; }
	bool testAgainst(glm::vec2 pos) {
		if (glm::length(this->pos + pos) - radius <= 0)
			return true;
		else
			return false;
	}

};