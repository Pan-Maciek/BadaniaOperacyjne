#pragma once
#include <vector>
#include <iostream>
#include "Obstacle.h"
#include "RectObstacle.h"
#include "CircleObstacle.h"
using namespace std;

struct Solution {
	vector<float> steps;
	float cost;


	Solution() = default;
	Solution(vector<float> steps, std::vector<Obstacle*> obstacles);

	static Solution random(int solution_size, std::vector<Obstacle*> obstacles);
};

