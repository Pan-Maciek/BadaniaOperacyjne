#include "Solution.h"
#include "Config.h"
#include <random>
#include <cmath>

random_device r;
default_random_engine random_engine(r());

// TODO: refactor 

float f1(float x) { return x; }
float f2(float x) { return 3 * x; }
float f3(vec2 position) { return 1000; }

float sd_box(vec2 p, vec2 b) {
    vec2 d = abs(p) - b;
    return length(max(d, vec2(0, 0))) + glm::min(glm::max(d.x, d.y), 0.0f);
}

bool world_check(vec2 position) {
    return sd_box(position, vec2(10.f, 10.f)) > 0;
}

float sd_circle(vec2 p, float r) {
    return length(p) - r;
}

bool detect_collision(vec2 position) {
    return world_check(position) || (sd_circle(position, 1) < 0);
}

float F(vector<float>& V) {
    float cost = 0.f;
    vec2 position = S;
    for (float angle : V) {
        vec2 v = { cos(angle) * STEP_SIZE, sin(angle) * STEP_SIZE };
        position += v;
        //if (length(position - T) < STEP_SIZE) {
        //    break;
        //}
        if (detect_collision(position)) {
            cost += f3(position);
        }
    }

    cost += f2(length(T - position));
    cost += f1(length(position - S));
    
    return cost;
}

Solution Solution::random(int solution_size) {
	static uniform_real_distribution<float> rng1(-M_PI, M_PI);
	static uniform_real_distribution<float> rng2(-MUTATION_ANGLE, MUTATION_ANGLE);
	vector<float> steps(solution_size);
    steps[0] = rng1(random_engine);
	for (int i = 1; i < solution_size; i++)
		steps[i] = steps[i-1] + rng2(random_engine);
	return Solution(steps);
}

Solution::Solution(vector<float> steps) : 
	cost(F(steps)), steps(steps) {}

