#include "pch.h"
#include "Network.h"

#include "RSA.h"

void Network::handleSecPubKey(
	SecPubKey *pkt){

	dec_key = pkt->pub_key;
	dec_n = pkt->n;
	enc_key = 79;
	enc_n = 10721;

	int priv_key = modexp(4519, 4519, enc_n);

	sendSecSessionKey(10721, priv_key);
}