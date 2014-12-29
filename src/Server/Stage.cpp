#include "stdafx.h"
#include "Stage.h"

#include "Unit.h"
#include "GameRoom.h"
#include "CollisionDetector.h"
#include "TrashPool.h"
#include "Ally.h"
#include "EnemySpawner.h"
#include "RepairArea.h"

#include "config.h"

Stage::Stage(GameRoom* gameroom, const int id)
	:gameroom(gameroom), id(id),
	enemyNum(0), bonusTimer(config::bonus_time_wait){

	collisionDetector = new CollisionDetector();
	trashPool = new TrashPool(this);
	spawner = new EnemySpawner(this);
	repairArea = new RepairArea();
	for (int i = 0; i < ALLY_MAX; ++i)
		ally[i] = new Ally();

	addUnit(repairArea);

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
	repairArea->init();
	for (int i = 0; i < ALLY_MAX; ++i)
		ally[i]->init();
}


void Stage::update(const float dt) {
	for (auto u : units) {
		u->update(dt);
	}
	collisionDetector->update(dt);
	trashPool->update(dt);
	repairArea->update(dt);

	if (enemyNum == 0) {
		bonusTimer -= dt;
		if (bonusTimer <= 0) {
			spawner->spawn(enemyBonus);
		}
	}
}


id_t Stage::addUnit(Unit* unit) {
	if (!unit)
		return INVALID_ID;
	unit->stage = this;
	return gameroom->addUnit(unit);
}

void Stage::removeUnit(Unit* unit) {
	if (!unit)
		return;
	gameroom->removeUnit(unit);
	unit->removed = true;
}

id_t Stage::addUnitImmediate(Unit* unit) {
	if (!unit)
		return INVALID_ID;

	auto it = std::find(units.begin(), units.end(), unit);
	if (it != units.end())
		return unit->id;

	// unit->stage = this;

	switch (unit->type)
	{
	case UT_PLAYER:
		ally[Ally::Type::allyPlayer]->push(unit);
		collisionDetector->addUnit(unit);
		break;
	case UT_ENEMY:
		ally[Ally::Type::allyEnemy]->push(unit);
		collisionDetector->addUnit(unit);
		enemyNum += 1;
		break;
	case UT_BULLET:
		break;
	case UT_TRASH:
		trashPool->push((Trash*)unit);
		break;
	default:
		break;
	}

	units.push_back(unit);
	return unit->id;
}

void Stage::removeUnitImmediate(Unit* unit) {
	if (!unit)
		return;

	auto it = std::find(units.begin(), units.end(), unit);
	if (it == units.end())
		return;

	switch (unit->type)
	{
	case UT_PLAYER:
		ally[Ally::Type::allyPlayer]->remove(unit);
		collisionDetector->removeUnit(unit);
		break;
	case UT_ENEMY:
		ally[Ally::Type::allyEnemy]->remove(unit);
		collisionDetector->removeUnit(unit);
		enemyNum -= 1;
		if (enemyNum == 0)
			bonusTimer = config::bonus_time_wait;
		break;
	case UT_BULLET:
		break;
	case UT_TRASH:
		trashPool->remove((Trash*)unit);
		break;
	default:
		break;
	}

	units.erase(it);
}


Unit* Stage::getUnit(const id_t id) {
	auto it = std::find_if(units.begin(), units.end(), [id](Unit* u){ return u->id == id; });
	if (it == units.end())
		return nullptr;
	return *it;
}
