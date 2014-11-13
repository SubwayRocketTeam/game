#include "pch.h"
#include "Network.h"

void Network::sendMoveStart(
	INT(x),INT(y)){

	move_start pkt;
	pkt.x = x;
	pkt.y = y;
	pkt.timestamp = GetTickCount();

	send(pkt);
}
void Network::sendMoveEnd(){
	move_end pkt;
	pkt.timestamp = GetTickCount();

	send(pkt);
}