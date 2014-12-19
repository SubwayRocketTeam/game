#include "pch.h"
#include "Network.h"

#include "objects/tags.h"
#include "objects/Unit.h"
#include "objects/ControlablePlayer.h"

using namespace cocos2d;

void Network::handleMove(
	MoveNoti *pkt){

	auto unit = Unit::getInstanceByID(
		pkt->id);

	if (!unit)
		return;

	unit->velocity.x = pkt->velocity_x;
	unit->velocity.y = pkt->velocity_y;

	printf("MOVE %d pos:(%f, %f) v:(%f %f)\n"
		, pkt->id
		, pkt->start_x, pkt->start_y
		, pkt->velocity_x, pkt->velocity_y);
	
	/*
	unit->setPosition(pkt->start_x, pkt->start_y);
	*/
	unit->runAction(
		EaseOut::create(
		MoveTo::create(
		1.f, Vec2(pkt->start_x, pkt->start_y))
		, 10.f)
		);
}

void Network::handleSyncRotationNoti(
	SyncRotationNoti *pkt){

	auto unit = Unit::getInstanceByID(
		pkt->id);
	auto player = ControlablePlayer::getInstance();

	if (!unit)
		return;

	/* 자신 플레이어 회전 패킷은 무시 */
	if(pkt->id == player->getID())
		return;

	unit->runAction(
		RotateTo::create(0.1, pkt->angle));
}

void Network::handleVacuum(
	Vacuum *pkt) {

	auto unit = (Player*)Unit::getInstanceByID(
		pkt->unit_id);

	if (!unit)
		return;

	unit->vacuume((Trash*)Unit::getInstanceByID(pkt->trash_id));
}