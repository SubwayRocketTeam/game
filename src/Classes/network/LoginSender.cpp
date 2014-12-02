#include "pch.h"
#include "Network.h"

void Network::sendLoginRequest(
	const char *user_id, const char *user_pw){

	LoginRequest pkt;
	strcpy(pkt.id, user_id);
	strcpy(pkt.pw, user_pw);

	send(pkt);
}