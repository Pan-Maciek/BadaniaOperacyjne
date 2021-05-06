#include "Generation.h"
#include <algorithm>
#include <random>

static random_device r;
static default_random_engine random_engine(r());

Generation::Generation(int population_size) :
    solutions(population_size), cum_sum(), cum_sum_value(0) { }

Generation Generation::random(int population_size, int solution_size, std::vector<Obstacle*> obstacles) {
    Generation gen(population_size);
    for (int i = 0; i < population_size; i++)
        gen.solutions[i] = Solution::random(solution_size,obstacles);
    return gen;
}

void Generation::sort() {
    if (is_sorted) return;
    std::sort(solutions.begin(), solutions.end(), [](const Solution& a, const Solution& b) {
        return a.cost < b.cost;
    });
    is_sorted = true;
}

void Generation::compute_cum_sum() {
    cum_sum.resize(solutions.size());
    cum_sum[0] = 1 / solutions[0].cost;
    for (int i = 1; i < cum_sum.size(); i++)
        cum_sum[i] = cum_sum[i - 1] + 1 / solutions[i].cost;
    cum_sum_value = cum_sum[cum_sum.size() - 1];
}

int binary_search_min(vector<float>& values, float value) {
    int min = 0, max = (int)values.size() - 1, c;
    while (min <= max) {
        c = min + (max - min) / 2;
        if (values[c] < value) min = c + 1;
        else max = c - 1;
    }
    return c;
}

vector<Solution> Generation::select_n(int n) {
    sort();

    if (cum_sum.empty())
        compute_cum_sum();

    uniform_real_distribution<float> rng(0, cum_sum_value);

    vector<Solution> selected(n);
    for (int i = 0, idx; i < n; i++) {
        idx = binary_search_min(cum_sum, rng(random_engine));
        selected[i] = solutions[idx];
    }

    return selected;
}

Solution Generation::best_solution() {
    sort();
    return solutions[0];
}

Generation::Generation(vector<Solution> solutions) :
    solutions(solutions), cum_sum(), cum_sum_value(0) { }

