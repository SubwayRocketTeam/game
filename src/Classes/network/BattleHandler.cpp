#include "pch.h"
#include "Network.h"

#include "objects/Player.h"
#include "objects/Unit.h"
#include "objects/Bullet.h"
#include "objects/Stage.h"

using namespace cocos2d;

void Network::handleUseSkillNoti(
	UseSkillNoti *pkt){

	auto unit = Unit::getInstanceByID(pkt->id);
	auto player = Player::getInstance();

	if(pkt->id == player->getID())
		return;

	unit->useSkill(
		pkt->skill_id,
		Vec2(pkt->x, pkt->y));
}
/*
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
*/