#include "pch.h"
#include "Network.h"
#include "GameRoom.h"

void Network::handleLoginResponse(
	LoginResponse *pkt){
	if (pkt->client_id)
		GameRoom::getInstance()->setMyId(pkt->client_id);
}