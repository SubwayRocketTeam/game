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

	if (!unit)
		return;

	if(pkt->id == player->getID())
		return;

	unit->useSkill(
		pkt->skill_id,
		Vec2(pkt->x, pkt->y));
}