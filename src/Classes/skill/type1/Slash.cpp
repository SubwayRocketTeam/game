#include "pch.h"
#include "Slash.h"

#include "audio/include/SimpleAudioEngine.h"

#include "objects/Unit.h"
#include "objects/Ally.h"
#include "objects/Bullet.h"
#include "objects/Stage.h"

#include "common/resource.h"

#include "ui/StatusConsole.h"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

void Slash::use(
	Unit *u,
	cocos2d::Vec2 pos){

	auto stage = Stage::getInstance(u->getStageID());

	auto bullet = Bullet::create();
	bullet->setPosition(u->getPosition());
	bullet->fire(pos.x, pos.y, 800);

	bullet->setUser(u);
	bullet->setRadius(10);
	bullet->setDamage(u->_ATTR(attack));
	bullet->setRange(u->_ATTR(range));
	bullet->setAllyID(u->getAllyID());
	bullet->setOpacity(0);
	bullet->runAction(
		FadeIn::create(0.25));

	stage->addChild(bullet, Z::bullet);
	
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect(R::Fire.c_str());

	/*
	auto slash = Sprite::create(R::SkillSlash);
	auto ally = Ally::getInstance(
		_OPPOSITE(u->getAllyID()));

	AttackData attackData;
	attackData.user = u;
	attackData.damage = 1;
	attackData.startPostion = u->getPosition();
	attackData.targetPostion = pos;
	attackData.radius = 100;
	attackData.halfAngle = 90;
	attackData.aggro = 10;

	ally->processAttack(u, attackData);

	slash->runAction(
		Sequence::create(
			FadeOut::create(0.4),
			RemoveSelf::create(),
			nullptr));
	slash->setRotation(
		u->getRotation());

	u->addChild(slash);
	*/
}