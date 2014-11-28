#include "pch.h"
#include "Random.h"

#include <stdlib.h>

void Random::setSeed(
	unsigned int seed[States]){
}
void Random::setIndex(
	unsigned int index){
}
unsigned int Random::getIndex(){
	return 0;
}

int Random::rand(){
	return ::rand();
}