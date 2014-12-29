#include "pch.h"
#include "Network.h"

#include "GameRoom.h"

#include "common/resource.h"

#include "objects/Stage.h"
#include "objects/Unit.h"
#include "objects/Enemy.h"
#include "objects/Player.h"
#include "objects/ControlablePlayer.h"
#include "objects/Ally.h"
#include "objects/CollisionDetector.h"
#include "objects/EnemyFactory.h"
#include "objects/Trash.h"
#include "objects/RepairArea.h"

void Network::handleSpawn(
	SpawnUnit *pkt){

	printf("ID %d / TYPE %d\n", pkt->id, pkt->unit_type);

	if (Unit::getInstanceByID(pkt->id))
		return;

	auto stage = Stage::getInstance(pkt->stage);
	Unit* unit = nullptr;
	int z = 0;

	switch (pkt->unit_type) {

	case UNIT_PLAYER:
	{
		// sub_type으로 플레이어 종류 선택
		unit = Player::create(pkt->stage, "type1.json");
		auto players = Stage::getInstance(pkt->stage)->getAlly(Ally::allyPlayer);
		players->push(unit);
		z = Z::unit;
		break;
	}
	case UNIT_PLAYER_ME:
	{
		// sub_type으로 플레이어 종류 선택
		unit = ControlablePlayer::create(pkt->stage, "type1.json");
		auto players = Stage::getInstance(pkt->stage)->getAlly(Ally::allyPlayer);
		players->push(unit);
		z = Z::unit;
		break;
	}

	case UNIT_TRASH:
	{
		auto trash = Trash::create();
		unit = trash;
		z = Z::trash;
		break;
	}

	case UNIT_ENEMY:
	{
		auto factory = EnemyFactory::getInstance();
		auto ally = Stage::getInstance(pkt->stage)->getAlly(Ally::Type::allyEnemy);
		auto e = factory->createEnemy(pkt->stage, (EnemyType)(pkt->sub_type - ENEMY_BASIC));
		e->resetAggro();
		ally->push(e);
		unit = e;
		z = Z::unit;
		break;
	}

	case UNIT_REPAIR_AREA:
	{
		unit = RepairArea::create();
		z = Z::repairArea;
		break;
	}

	}

	if (unit) {
		unit->setID(pkt->id);
		unit->setPosition(pkt->x, pkt->y);
		unit->setStageID(pkt->stage);
		stage->addChild(unit, z);
	}
}
void Network::handleRemoveUnit(
	RemoveUnit *pkt){

	auto unit = Unit::getInstanceByID(pkt->id);

	if (!unit)
		return;

	auto ally = Stage::getInstance(unit->getStageID())->getAlly(unit->getAllyID());
	ally->remove(unit);
	unit->remove();
}
void Network::handleSetPhysics(
	SetPhysics *pkt) {
	auto unit = Unit::getInstanceByID(pkt->id);

	if (unit != nullptr){
		unit->velocity.set(pkt->velocity_x, pkt->velocity_y);
		unit->acceleration.set(pkt->acceleration_x, pkt->acceleration_y);
		unit->friction = pkt->friction;
	}
}
