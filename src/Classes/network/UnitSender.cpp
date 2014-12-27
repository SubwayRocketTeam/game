#include "pch.h"
#include "Network.h"

void Network::sendSpawnRequest(
	int unitType){

	SpawnRequest pkt;
	pkt.enemy_type = unitType;
	send(pkt);
}