#include "pch.h"
#include "Network.h"

void Network::sendFireBullet(
	int bulletType,
	float x,float y,
	float directionX,float directionY){

	FireBullet pkt;
	pkt.bullet_type = bulletType;
	pkt.x = x, pkt.y = y;
	pkt.direction_x = directionX;
	pkt.direction_y = directionY;
	send(pkt);
}