#include "pch.h"
#include "EnemyShot.h"

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

void EnemyShot::use(
	Unit *u,
	cocos2d::Vec2 pos){

	auto stage = Stage::getInstance(u->getStageID());

	auto bullet = Bullet::create(2);
	bullet->setPosition(u->getPosition());
	bullet->fire(pos.x, pos.y, 600.f);

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
}