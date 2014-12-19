#include "pch.h"
#include "Network.h"

void Network::sendMove(
	float direction_x, float direction_y){
	
	puts("move");

	Move pkt;
	pkt.direction_x = direction_x;
	pkt.direction_y = direction_y;
	send(pkt);
}

void Network::sendSyncRotation(
	float angle){
	
	puts("rotate");

	SyncRotation pkt;
	pkt.angle = angle;
	send(pkt);
}