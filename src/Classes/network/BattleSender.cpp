#include "pch.h"
#include "Network.h"

#include "objects/Unit.h"
#include "objects/Bullet.h"
#include "objects/Stage.h"

void Network::handleFireBulletNoti(
	FireBulletNoti *pkt){

	auto bullet = Bullet::create();
	auto stage = Stage::getInstance(pkt->team);

	bullet->setPosition(pkt->x,pkt->y);
	bullet->fire(
		pkt->velocity_x, pkt->velocity_y,
		1);
	stage->addChild(bullet);
}