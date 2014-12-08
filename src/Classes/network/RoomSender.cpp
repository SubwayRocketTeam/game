#include "pch.h"
#include "Network.h"

void Network::sendEnterRoom(){
	EnterRoom pkt;
	send(pkt);
}
void Network::sendLeaveRoom(){
	LeaveRoom pkt;
	send(pkt);
}
void Network::sendReady(){
	Ready pkt;
	send(pkt);
}