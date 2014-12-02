#include "pch.h"
#include "Network.h"

void Network::sendChatMessage(
	const char *msg){

	ChatMessage pkt;
	strcat_s(pkt.msg, msg);
	send(pkt);
}