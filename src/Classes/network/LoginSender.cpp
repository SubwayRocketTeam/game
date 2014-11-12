#include "pch.h"
#include "Network.h"

void Network::sendLoginRequest(
	STRING(user_id), STRING(user_pw)){

	login_request pkt;
	strcpy(pkt.user_id, user_id);
	strcpy(pkt.user_pw, user_pw);

	send(pkt);
}