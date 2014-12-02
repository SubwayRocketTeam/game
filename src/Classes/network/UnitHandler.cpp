#include "pch.h"
#include "Network.h"

#include "common/resource.h"

#include "objects/Stage.h"
#include "objects/Unit.h"
#include "objects/Player.h"

void Network::handleSpawn(
	Spawn *pkt){

	if(pkt->unit_type){
		auto player = Player::getInstance();
		player->setID(pkt->id);
	}
	else{
		auto stage = Stage::getInstance(0);
		auto unit = Unit::create(R::PlayerBody);
	
		unit->setID(pkt->id);
		unit->setPosition(pkt->x,pkt->y);
		stage->addChild(unit);
	}
}
