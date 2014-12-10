#pragma once

#include <random>

class Random{
public:
	Random();
	Random(int seed);
	virtual ~Random();

	void setSeed(
		int seed);
	int rand();

private:
	std::mt19937 rnd;
	int seed;
};