#pragma once
#include <cmath>
#include <glm/glm.hpp>
using namespace glm;

const int WINDOW_WIDTH = 920;
const int WINDOW_HEIGHT = 920;

const float STEP_SIZE = 0.3f;

const float MUTATION_CHANCE = 0.4;
const float MUTATION_ANGLE = M_PI / 14;
const float KEEP_BEST = 0;

const int POPULATION_SIZE = 100;
const int SOLUTION_SIZE = 45;

//Start, Target Definitions
const vec2 S(0, -5);
const vec2 T(0, 5);

//Obstacles definitions

const int FPS = 15;

// PSO
const float w =	1;
const float c1 = 1.41;
const float c2 = 1.41;
const float r1 = 0.5;
const float r2 = 0.5;