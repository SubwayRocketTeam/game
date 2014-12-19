#include "pch.h"
#include "Network.h"

void Network::sendMove(
	float direction_x, float direction_y){
	
	Move pkt;
	pkt.direction_x = direction_x;
	pkt.direction_y = direction_y;
	send(pkt);
}

void Network::sendSyncRotation(
	float angle){
	
	SyncRotation pkt;
	pkt.angle = angle;
	send(pkt);
}