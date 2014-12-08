#include "pch.h"
#include "Network.h"

#include "common/resource.h"

#include "objects/Stage.h"
#include "objects/Unit.h"
#include "objects/Player.h"
#include "objects/Ally.h"

void Network::handleSpawn(
	SpawnUnit *pkt){

	if(pkt->unit_type){
		auto player = Player::getInstance();
		player->setID(pkt->id);
	}
	else if(Unit::getInstanceByID(pkt->id) == nullptr){
		auto stage = Stage::getInstance(0);
		auto players = Ally::getInstance(
			Ally::allyPlayer);
		auto unit = Unit::create(R::PlayerBody);
	
		unit->setID(pkt->id);
		unit->setPosition(pkt->x,pkt->y);
		stage->addChild(unit);
		players->push(unit);
	}
}
