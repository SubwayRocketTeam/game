#include "pch.h"
#include "Network.h"

void Network::sendSecHello(){
	SecHello pkt;
	send(pkt);
}
void Network::sendSecSessionKey(
	int n, int pub_key){

	SecSessionKey pkt;
	pkt.n = n;
	pkt.session_key = pub_key;
	send(pkt);

	ssl_ready = true;
}