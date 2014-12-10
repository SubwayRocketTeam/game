#include "pch.h"
#include "Network.h"

void Network::sendUseSkill(
	int skillID,
	float x,float y){

	UseSkill pkt;
	pkt.skill_id = skillID;
	pkt.x = x;
	pkt.y = y;
	send(pkt);
}
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
