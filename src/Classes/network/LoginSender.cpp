#include "pch.h"
#include "Network.h"

void Network::sendLoginRequest(
	const char *nickname){

	LoginRequest pkt;
	strcpy_s(pkt.nickname, nickname);

	send(pkt);
}