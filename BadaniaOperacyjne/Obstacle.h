#pragma once
#include <glm/glm.hpp>
class Obstacle {
public:
	glm::vec2 pos;
	virtual bool testAgainst(glm::vec2 pos)=0;

};