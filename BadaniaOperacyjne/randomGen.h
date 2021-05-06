#pragma once
#include <random>
class RandomGen {
public:
	std::random_device rd;
	std::default_random_engine e;
	RandomGen() {e= std::default_random_engine(rd());}
	long double rand(double min, double max);
	long long rand(long long min, long long max);
	int rand(int min, int max);

};

