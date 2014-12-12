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
void Network::sendReady(
	int robot_id){

	Ready pkt;
	pkt.robot_id = 0;
	send(pkt);
}