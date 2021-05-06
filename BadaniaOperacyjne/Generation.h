#pragma once
#include "Solution.h"

struct Generation {
    vector<Solution> solutions;

    Generation(int population_size);
    Generation(vector<Solution> solutions);

    void sort();
    vector<Solution> select_n(int n);
    Solution best_solution();
    static Generation random(int population_size, int solution_size, std::vector<Obstacle*> obstacles);

private:
    bool is_sorted = false;
    vector<float> cum_sum;
    float cum_sum_value;
    void compute_cum_sum();
};

