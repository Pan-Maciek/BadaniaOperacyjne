#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Obstacle.h"
#include "RectObstacle.h"
#include "CircleObstacle.h"
#include "Particle.h"
#include "RandomGen.h"
struct PSO {
	RandomGen randomGen;
	glm::vec2 mapBounds;
	glm::vec2 start;
	glm::vec2 end;
	std::vector<float> bestPos;
	std::vector<Obstacle*> obstacles;
	int solutionSize;
	float stepSize;
	float bestCost;

	float evaluate(std::vector<float> pos);
	void initialize(int numOfParticles, glm::vec2 velocityBounds);
	
	PSO(glm::vec2 mapBounds, glm::vec2 start, glm::vec2 end, int solutionSize, float stepSize, int numOfParticles, glm::vec2 velocityInitialBounds);

	~PSO() {for(int i = 0; i < obstacles.size(); i++) delete obstacles[i];}

	void step();
	std::vector<Particle> particles;
	void addRectObstacle(glm::vec2 pos, glm::vec2 size);
	void addCircleObstacle(glm::vec2 pos, double radius);
	float f1(float x) { return x; }
	float f2(float x) { return 3 * x; }
	float f3(glm::vec2 position) { return 1000; }
};