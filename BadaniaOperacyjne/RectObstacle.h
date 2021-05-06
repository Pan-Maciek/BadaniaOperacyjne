#pragma once
#include "Obstacle.h"
class RectObstacle :public Obstacle {
public:
	glm::vec2 size;
	RectObstacle(glm::vec2 pos, glm::vec2 size) {
		this->size = size;
		this->pos = pos;
		this->shape = new sf::RectangleShape(sf::Vector2f(size.x,size.y));
		shape->setOrigin(size.x/2,size.y/2);
		shape->setPosition(pos.x, pos.y);
		shape->setFillColor(sf::Color::Red);
	}

	bool testAgainst(glm::vec2 pos) {
		glm::vec2 d = glm::abs(pos-this->pos) - this->size;
		if(glm::length(glm::max(d, 0.f)) + glm::min(glm::max(d.x, d.y), 0.f)<=0)
			return true;
		else
			return false;
	}

};