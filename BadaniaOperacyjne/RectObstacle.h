#pragma once
#include "Obstacle.h"
class RectObstacle :public Obstacle {
public:
	glm::vec2 size;
	RectObstacle(glm::vec2 pos, glm::vec2 size) { this->size = size; this->pos = pos; }
	bool testAgainst(glm::vec2 pos) {
		glm::vec2 d = glm::abs(this->pos+pos) - this->size;
		if(glm::length(glm::max(d, 0.f)) + glm::min(glm::max(d.x, d.y), 0.f)<=0)
			return true;
		else
			return false;
	}
};