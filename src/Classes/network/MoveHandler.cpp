#include "pch.h"
#include "Network.h"

#include "objects/Unit.h"

void Network::handleMoveStart(
	MoveStartNoti *pkt){

	auto unit = Unit::getInstanceByID(
		pkt->id);

	unit->velocity.x = pkt->velocity_x;
	unit->velocity.y = pkt->velocity_y;

	printf("move %d / %f %f\n",
		pkt->id,
		pkt->velocity_x, pkt->velocity_y);
}
void Network::handleMoveEnd(
	MoveEndNoti *pkt){

	auto unit = Unit::getInstanceByID(
		pkt->id);

	unit->velocity.set(0,0);

	/*
	printf("adj %f %f / %f %f\n",
		unit->getPositionX(), unit->getPositionY(),
		pkt->end_x, pkt->end_y);
	unit->setPosition(pkt->end_x, pkt->end_y);
	*/

	printf("move end %d\n", pkt->id);
}