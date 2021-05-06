#pragma once
#include <glm/glm.hpp>
#include <vector>
class Particle {
public:
	std::vector<float> position;
	std::vector<float> velocity;
	std::vector<float> bestPos;
	std::vector<float>* bestSwarmPos;
	float cost;

	Particle(std::vector<float> pos, std::vector<float> vel, std::vector<float>* bestSwarmPos) {
		this->position = pos;
		this->velocity = vel; 
		this->bestPos = pos; 
		this->bestSwarmPos = bestSwarmPos;
	}	

};