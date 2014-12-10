#include "stdafx.h"
#include "Stage.h"

#include "Unit.h"
#include "GameRoom.h"
#include "CollisionDetector.h"
#include "TrashPool.h"
#include "Ally.h"
#include "EnemySpawner.h"

Stage::Stage(GameRoom* gameroom, const int id)
	:gameroom(gameroom), id(id) {

	collisionDetector = new CollisionDetector();
	trashPool = new TrashPool();
	spawner = new EnemySpawner();
	for (int i = 0; i < ALLY_MAX; ++i)
		ally[i] = new Ally();

	init();
}

Stage::~Stage() {

}

void Stage::init() {
	units.clear();
	collisionDetector->init();
	trashPool->init();
	spawner->init();
	for (int i = 0; i < ALLY_MAX; ++i)
		ally[i]->init();
}


void Stage::update(const float dt) {
	for (auto u : units) {
		u->update(dt);
	}
	collisionDetector->update(dt);
	trashPool->update(dt);
//	spawner->update(dt);
}


void Stage::addUnit(Unit* unit) {
	if (unit)
		units.push_back(unit);
}

void Stage::removeUnit(const id_t id) {
	auto it = std::find_if(units.begin(), units.end(), [id](Unit* u){ return u->id == id; });
	if (it != units.end())
		units.erase(it);
}


Unit* Stage::getUnit(const id_t id) {
	auto it = std::find_if(units.begin(), units.end(), [id](Unit* u){ return u->id == id; });
	if (it == units.end())
		return nullptr;
	return *it;
}
