#pragma once
#include <glm/glm.hpp>
#include <vector>
class Particle {
public:
	std::vector<float> position;
	std::vector<float> velocity;
	std::vector<float> bestPos;
	float cost;
	float bestCost;

	Particle(std::vector<float> pos, std::vector<float> vel) {
		this->position = pos;
		this->velocity = vel; 
		this->bestPos = pos; 
	}	

};