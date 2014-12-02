#include "pch.h"
#include "Network.h"

#include "common/resource.h"

#include "objects/Stage.h"
#include "objects/Unit.h"

/* TODO : 수정, 스테이지 id, 유닛 id 등 */
void Network::handleEnterRoomNoti(
	EnterNoti *pkt){

	auto stage = Stage::getInstance(0);
	auto unit = Unit::create(R::PlayerBody);

	unit->setID(pkt->clientId);
	stage->addChild(unit);
}
void Network::handleLeaveRoomNoti(
	LeaveNoti *pkt){

	auto stage = Stage::getInstance(0);
	auto unit = Unit::getInstanceByID(
		pkt->clientId);

	stage->removeChild(unit);
}