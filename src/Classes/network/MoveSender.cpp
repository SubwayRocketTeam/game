#include "pch.h"
#include "Network.h"

void Network::sendMoveStart(
	float direction_x, float direction_y){

	MoveStart pkt;
	pkt.direction_x = direction_x;
	pkt.direction_y = direction_y;
	send(pkt);
}
void Network::sendMoveEnd(
	float delta){

	MoveEnd pkt;
	send(pkt);
}