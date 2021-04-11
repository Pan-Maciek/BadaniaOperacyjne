#pragma once
#include "Generation.h"
#include "Solution.h"
#include "Config.h"

struct GeneticOptimizer {
    const int population_size;
    Generation current_generation;

    GeneticOptimizer(int population_size, int solution_size);

    void step();
    Solution best_solution();
};

