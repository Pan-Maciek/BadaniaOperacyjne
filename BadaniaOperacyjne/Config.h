#pragma once
#include <cmath>
#include <glm/glm.hpp>

using namespace glm;

	extern int WINDOW_WIDTH;
	extern int WINDOW_HEIGHT;

	extern float STEP_SIZE;

	extern float MUTATION_CHANCE;
	extern float MUTATION_ANGLE;
	extern float KEEP_BEST;

	extern int POPULATION_SIZE;
	extern int SOLUTION_SIZE;

	//Start, Target Definitions
	const vec2 S=vec2(0, -5);
	const vec2 T= vec2(0, 5);

	//Obstacles definitions



	const int FPS = 15;

