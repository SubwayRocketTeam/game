#include "pch.h"
#include "Explosion.h"

#include "audio/include/SimpleAudioEngine.h"

#include "objects/Unit.h"
#include "objects/Ally.h"
#include "objects/Bullet.h"
#include "objects/Stage.h"

#include "common/resource.h"
#include "common/global.h"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

void Explosion::use(
	Unit *u,
	cocos2d::Vec2 pos){
	circleShot(nullptr, u, CC_DEGREES_TO_RADIANS(rand() % 360));
}

void Explosion::circleShot(
	Ref* sender,
	Unit *u,
	float angle){

	auto stage = Stage::getInstance(0);

	for (int i = 0; i < 32; ++i){
		auto bullet = Bullet::create(2);
		Vec2 direction = Vec2::UNIT_X.rotateByAngle(
			Vec2::ZERO, CC_DEGREES_TO_RADIANS(angle + 360/31 * i));
		bullet->setPosition(u->getPosition());
		bullet->fire(direction, 1200.f);

		bullet->setUser(u);
		bullet->setRadius(10);
		bullet->setDamage(u->_ATTR(attack));
		bullet->setRange(u->_ATTR(range));
		bullet->setAllyID(u->getAllyID());

		stage->addChild(bullet, Z::bullet);
	}


	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect(R::Fire.c_str());
}
