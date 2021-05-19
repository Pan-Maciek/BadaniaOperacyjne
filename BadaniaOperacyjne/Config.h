#pragma once
#include <cmath>
#include <glm/glm.hpp>

using namespace glm;

 static int WINDOW_WIDTH = 920;
 static int WINDOW_HEIGHT = 920;

 static float STEP_SIZE = 0.3f;

 static float MUTATION_CHANCE = 0.4;
 static float MUTATION_ANGLE = M_PI / 14;
 static float KEEP_BEST = 0;

 static int POPULATION_SIZE = 50;
 static int SOLUTION_SIZE = 65;

//Start, Target Definitions
const vec2 S(0, -5);
const vec2 T(0, 5);

//Obstacles definitions



const int FPS = 15;

