#pragma once

#include "IDDispenser.h"

#define ALLY_MAX 2

class Unit;
class GameRoom;
class CollisionDetector;
class TrashPool;
class Ally;
class EnemySpawner;
class RepairArea;

class Stage {
public:
	Stage(GameRoom* gameroom, const int id);
	~Stage();
	void init();

	void update(const float dt);

	id_t addUnit(Unit* unit);
	void removeUnit(Unit* unit);
	id_t addUnitImmediate(Unit* unit);		// GameRoom에서만 불러야 한다.
	void removeUnitImmediate(Unit* unit);	// GameRoom에서만 불러야 한다.

	Unit* getUnit(const id_t id);

public:
	GameRoom* const gameroom;
	const int id;

	CollisionDetector* collisionDetector;
	TrashPool* trashPool;
	Ally* ally[ALLY_MAX];
	EnemySpawner* spawner;
	RepairArea* repairArea;

private:
	std::vector<Unit*> units;

	int enemyNum;
	float bonusTimer;

};