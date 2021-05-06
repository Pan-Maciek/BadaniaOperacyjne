#pragma once
#include "Generation.h"
#include "Solution.h"
#include "Config.h"

struct GeneticOptimizer {
    const int population_size;
    Generation current_generation;
    std::vector<Obstacle*> obstacles;

    GeneticOptimizer(int population_size, int solution_size );

    void step();
    Solution best_solution();
    void addRectObstacle(glm::vec2 pos, glm::vec2 size);
    void addCircleObstacle(glm::vec2 pos, double radius);
};

