#include "pch.h"
#include "Network.h"

void Network::sendSpawnRequest(
	int unitType){

	SpawnRequest pkt;
	pkt.unit_type = unitType;
	send(pkt);
}