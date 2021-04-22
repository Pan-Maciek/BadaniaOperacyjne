#include "GeneticOptimizer.h"
#include <random>
#include <iostream>

static random_device r;
static default_random_engine random_engine(r());

Solution crossover(const Solution& a, const Solution& b) {
    vector<float> steps(a.steps.size());

    static uniform_real_distribution<float> mutation_chance(0, 1);
    static uniform_real_distribution<float> mutation_angle(-MUTATION_ANGLE, MUTATION_ANGLE);
    int split = uniform_int_distribution<int>(0, b.steps.size() - 1)(random_engine);

    for (int i = 0; i < split; i++)
        steps[i] = a.steps[i] + (mutation_chance(random_engine) < MUTATION_CHANCE ? mutation_angle(random_engine) : 0);

    for (int i = split; i < b.steps.size(); i++)
        steps[i] = b.steps[i] + (mutation_chance(random_engine) < MUTATION_CHANCE ? mutation_angle(random_engine) : 0);

    return Solution(steps);
}

GeneticOptimizer::GeneticOptimizer(int population_size, int solution_size) :
    current_generation(Generation::random(population_size, solution_size)),
    population_size(population_size)
{ current_generation.sort(); }

void GeneticOptimizer::step() {
    vector<Solution> next_generation(population_size);

    int i = 0;

    

    for (; i < (int)KEEP_BEST * population_size; i++)
        next_generation[i] = current_generation.solutions[i];

    for (; i < population_size; i++) {
        auto parents = current_generation.select_n(2);
        next_generation[i] = crossover(parents[0], parents[1]);
    }

    current_generation = Generation(next_generation);
    current_generation.sort();

    for (int j = 0; j < population_size; j++) {
        cout << j << ": " << current_generation.solutions[j].cost << endl;
    }
}

Solution GeneticOptimizer::best_solution() {
    return current_generation.best_solution();
}
