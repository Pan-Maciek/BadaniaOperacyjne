#pragma once
#include "randomGen.h"
long double RandomGen::rand(double min, double max) {
	std::uniform_real_distribution<> d(min, max);
	long double result = d(e);
	return result;
}

long long RandomGen::rand(long long min, long long max) {
	std::uniform_real_distribution<> d(min, max);
	long long result = d(e);
	return result;
}


int RandomGen::rand(int min, int max) {
	std::uniform_real_distribution<> d(min, max);
	int result = d(e);
	return result;
}