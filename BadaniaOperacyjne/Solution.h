#pragma once
#include <vector>
#include <iostream>
using namespace std;

struct Solution {
	vector<float> steps;
	float cost;

	Solution() = default;
	Solution(vector<float> steps);

	static Solution random(int solution_size);
};

