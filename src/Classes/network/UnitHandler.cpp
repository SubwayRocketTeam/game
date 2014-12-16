#include "pch.h"
#include "Network.h"

#include "common/resource.h"

#include "objects/Stage.h"
#include "objects/Unit.h"
#include "objects/Enemy.h"
#include "objects/Player.h"
#include "objects/ControlablePlayer.h"
#include "objects/Ally.h"
#include "objects/CollisionDetector.h"
#include "objects/EnemyFactory.h"

void Network::handleSpawn(
	SpawnUnit *pkt){

	printf("ID %d / TYPE %d\n", pkt->id, pkt->unit_type);

	if (Unit::getInstanceByID(pkt->id))
		return;

	auto stage = Stage::getInstance(pkt->stage);
	Unit* unit = nullptr;
	int z = 0;

	switch (pkt->unit_type) {

	case 0:
	{
		auto players = Ally::getInstance(Ally::allyPlayer);
		unit = Player::create("type1.json");
		players->push(unit);
		z = Z::unit;
		break;
	}

	case 1:
	{
		unit = ControlablePlayer::getInstance();
		unit->setID(pkt->id);
		unit->setPosition(pkt->x, pkt->y);
		return;
	}

	case 10:
	case 11:
	case 12:
	case 13:
	{
		auto factory = EnemyFactory::getInstance();
		auto ally = Ally::getInstance(Ally::Type::allyEnemy);
		auto e = factory->createEnemy((EnemyType)(pkt->unit_type - 10));
		e->resetAggro();
		ally->push(e);
		unit = e;
		z = Z::unit;
		break;
	}

	}

	if (unit) {
		unit->setID(pkt->id);
		unit->setPosition(pkt->x, pkt->y);
		stage->addChild(unit, z);
	}
}
void Network::handleRemoveUnit(
	RemoveUnit *pkt){

	auto unit = Unit::getInstanceByID(pkt->id);

	if(unit != nullptr){
		auto stage = Stage::getInstance(0);
		auto players = Ally::getInstance(
			Ally::Type::allyPlayer);

		players->remove(unit);
		unit->setOpacity(128);
		//stage->removeChild(unit);
	}
}