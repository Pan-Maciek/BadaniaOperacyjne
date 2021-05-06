#pragma once
#include "Obstacle.h"
class CircleObstacle :public Obstacle {
public:
	double radius;
	CircleObstacle(glm::vec2 pos, double radius) { 
		this->radius = radius; 
		this->pos = pos; 
		this->shape = new sf::CircleShape(radius);
		shape->setOrigin(radius, radius);
		shape->setPosition(pos.x, pos.y);
		shape->setFillColor(sf::Color::Red);
	}

	bool testAgainst(glm::vec2 pos) {
		if (glm::length(pos-this->pos ) - radius <= 0)
			return true;
		else
			return false;
	}

};