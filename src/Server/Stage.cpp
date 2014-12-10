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
	trashPool = new TrashPool(this);
	spawner = new EnemySpawner(this);
	for (int i = 0; i < ALLY_MAX; ++i)
		ally[i] = new Ally();

	init();
}

Stage::~Stage() {
	SAFE_DELETE(collisionDetector);
	SAFE_DELETE(trashPool);
	SAFE_DELETE(spawner);
	for (int i = 0; i < ALLY_MAX; ++i)
		SAFE_DELETE(ally[i]);
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
}


id_t Stage::addUnit(Unit* unit) {
	if (!unit)
		return INVALID_ID;

	switch (unit->type)
	{
	case UT_PLAYER:
		ally[Ally::Type::allyPlayer]->push(unit);
		collisionDetector->addUnit(unit);
		break;
	case UT_ENEMY:
		break;
		ally[Ally::Type::allyEnemy]->push(unit);
		collisionDetector->addUnit(unit);
	case UT_BULLET:
		collisionDetector->addUnit(unit);
		break;
	case UT_TRASH:
		trashPool->push((Trash*)unit);
		break;
	default:
		break;
	}

	units.push_back(unit);
	return gameroom->addUnit(unit);
}

void Stage::removeUnit(Unit* unit) {
	if (!unit)
		return;
	gameroom->removeUnit(unit);
}

void Stage::removeUnitImmediate(Unit* unit) {
	if (!unit)
		return;

	switch (unit->type)
	{
	case UT_PLAYER:
		ally[Ally::Type::allyPlayer]->remove(unit);
		collisionDetector->removeUnit(unit);
		break;
	case UT_ENEMY:
		break;
		ally[Ally::Type::allyEnemy]->remove(unit);
		collisionDetector->removeUnit(unit);
	case UT_BULLET:
		collisionDetector->removeUnit(unit);
		break;
	case UT_TRASH:
		trashPool->remove((Trash*)unit);
		break;
	default:
		break;
	}

	auto it = std::find(units.begin(), units.end(), unit);
	if (it != units.end())
		units.erase(it);

	gameroom->removeUnit(unit);
}


Unit* Stage::getUnit(const id_t id) {
	auto it = std::find_if(units.begin(), units.end(), [id](Unit* u){ return u->id == id; });
	if (it == units.end())
		return nullptr;
	return *it;
}
