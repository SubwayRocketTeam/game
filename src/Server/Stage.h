#pragma once

#include "IDDispenser.h"
class Unit;

class Stage {
public:
	Unit* getUnit(const id_t id);

private:
	//	CollisionDetector;
	//	TrashPool;
	//	Ally[2];
	//	EnemySpawner;

	std::vector<Unit*> units;
};