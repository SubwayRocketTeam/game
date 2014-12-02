#include "pch.h"
#include "Network.h"

#include "objects/Unit.h"

void Network::handleMoveStart(
	MoveStartResponse *pkt){

	auto unit = Unit::getInstanceByID(
		pkt->id);

	unit->velocity.x = pkt->velocity_x;
	unit->velocity.y = pkt->velocity_y;

	printf("move %d\n", pkt->id);
}
void Network::handleMoveEnd(
	MoveEndResponse *pkt){

	auto unit = Unit::getInstanceByID(
		pkt->id);

	unit->velocity.set(0,0);

	printf("move end %d\n", pkt->id);
}