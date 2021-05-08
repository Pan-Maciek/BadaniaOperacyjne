#include "PSO.h"
#include "Config.h"
#include <iostream>

std::vector<float> operator+(const std::vector<float>& a, const std::vector<float>& b);
std::vector<float> operator-(const std::vector<float>&a, const std::vector<float>&b);
std::vector<float> operator*(const float f, const std::vector<float>&a);
std::ostream& operator<<(std::ostream & os, const std::vector<float>& a);

PSO::PSO(glm::vec2 mapBounds, glm::vec2 start, glm::vec2 end, int solutionSize, float stepSize, int numOfParticles, glm::vec2 velocityInitialBounds) {
	this->mapBounds = mapBounds;
	this->start = start;
	this->end = end;
	this->solutionSize = solutionSize;
	this->stepSize = stepSize;
	initialize(numOfParticles, velocityInitialBounds);
}

void PSO::initialize(int numOfParticles,glm::vec2 velocityBounds){
	for (int i = 0; i < numOfParticles; i++) {
		std::vector<float> pos;
		std::vector<float> vel;
		for (int y = 0; y < solutionSize; y++) {
			pos.push_back(randomGen.rand(-M_PI, M_PI));
			vel.push_back(randomGen.rand(velocityBounds.x, velocityBounds.y));
		}
		Particle particle(pos, vel);
		particles.push_back(particle);
	}
	bestPos = particles[0].position;
	bestCost = INFINITY;
}

void PSO::addRectObstacle(glm::vec2 pos,glm::vec2 size) {
	RectObstacle* obstacle=new RectObstacle(pos, size);
	this->obstacles.push_back(obstacle);
}

void PSO::addCircleObstacle(glm::vec2 pos, double radius) {
	CircleObstacle* obstacle=new CircleObstacle(pos, radius);
	this->obstacles.push_back(obstacle);
}

float PSO::evaluate(const std::vector<float> pos) {
	float cost = 0.f;
	glm::vec2 position = start;
	for (float angle :pos) {
		glm::vec2 v = { cos(angle) * stepSize, sin(angle) * stepSize };
		position += v;

		for (auto obstacle : obstacles) {
			if (obstacle->testAgainst(position)) {
				cost += f3(position);
			}
		}
	}

	cost += f2(length(end - position));
	cost += f1(length(position - start));
	return cost;
		
}

void PSO::step() {
	//evaluate
	auto pBestPost = bestPos;
	for (auto& particle:particles) {
		float cost = particle.cost = evaluate(particle.position);
		if (cost < bestCost) {
			bestCost = cost;
			bestPos = particle.position;
		}
		
		auto& vi = particle.velocity = w * particle.velocity + (c1 * r1) * (particle.bestPos - particle.position) + (c2 * r2) * (pBestPost - particle.position);
		if (cost < particle.bestCost) {
			particle.bestPos = particle.position;
			particle.bestCost = cost;
		}
		particle.position = particle.position + vi;
	}

}


std::vector<float> operator+(const std::vector<float>& a, const std::vector<float>& b) {
	assert(a.size() == b.size());
	std::vector<float> result(a.size());
	for (int i = 0; i < a.size(); i++)
		result[i] = a[i] + b[i];
	return result;
}

std::vector<float> operator-(const std::vector<float>& a, const std::vector<float>& b) {
	assert(a.size() == b.size());
	std::vector<float> result(a.size());
	for (int i = 0; i < a.size(); i++)
		result[i] = a[i] - b[i];
	return result;
}

std::vector<float> operator*(const float f, const std::vector<float>& a) {
	std::vector<float> result(a.size());
	for (int i = 0; i < a.size(); i++)
		result[i] = f * a[i];
	return result;
}


std::ostream& operator<<(std::ostream & os, const std::vector<float>& a) {
	for (int i = 0; i < a.size(); i++)
		std::cout << a[i] << ' ';
	return os;
}

