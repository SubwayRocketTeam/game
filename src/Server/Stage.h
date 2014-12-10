#pragma once

#include "IDDispenser.h"

#define ALLY_MAX 2

class Unit;
class GameRoom;
class CollisionDetector;
class TrashPool;
class Ally;
class EnemySpawner;

class Stage {
public:
	Stage(GameRoom* gameroom, const int id);
	~Stage();
	void init();

	void update(const float dt);

	void addUnit(Unit* unit);		// GameRoom���� �ҷ��� �Ѵ�.
	void removeUnit(const id_t id); // GameRoom���� �ҷ��� �Ѵ�.

	Unit* getUnit(const id_t id);

public:
	const GameRoom* gameroom;
	const int id;

	CollisionDetector* collisionDetector;
	TrashPool* trashPool;
	Ally* ally[ALLY_MAX];
	EnemySpawner* spawner;

private:

	std::vector<Unit*> units;
};