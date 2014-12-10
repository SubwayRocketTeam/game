#include "random.h"

using namespace std;

Random::Random(){
}
Random::Random(int seed){
	setSeed(seed);
}
Random::~Random(){
}

void Random::setSeed(
	int _seed){

	rnd.seed(_seed);
	seed = _seed;
}
int Random::rand(){
	uniform_int_distribution<int> dist;
	return dist(rnd);
}