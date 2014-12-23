#include "stdafx.h"
#include "Spiral.h"

#include "Unit.h"
#include "Ally.h"
#include "Bullet.h"
#include "Stage.h"

#include "common/resource.h"

void Spiral::use(
	Unit *u,
	Vec2 pos){
	/*
	u->runAction(
		Sequence::create(
		CallFuncN::create(CC_CALLBACK_1(Spiral::circleShot, this, u, 0.f)),
		DelayTime::create(15.f / Global::fps),
		CallFuncN::create(CC_CALLBACK_1(Spiral::circleShot, this, u, 22.5f)),
		DelayTime::create(15.f / Global::fps),
		CallFuncN::create(CC_CALLBACK_1(Spiral::circleShot, this, u, 45.f)),
		DelayTime::create(15.f / Global::fps),
		CallFuncN::create(CC_CALLBACK_1(Spiral::circleShot, this, u, 67.5f)),
		nullptr
		));
	*/
}

void Spiral::update(
	Unit *u,
	float dt) {

	if (u->skillPhase == 0) {
		circleShot(u, 0.f);
		u->skillPhase = 1;
	}
	else if (u->skillPhase == 1 && u->skillTimer > 0.25f) {
		circleShot(u, 22.5f);
		u->skillPhase = 2;
	}
	else if (u->skillPhase == 2 && u->skillTimer > 0.5f) {
		circleShot(u, 45.f);
		u->skillPhase = 3;
	}
	else if (u->skillPhase == 3 && u->skillTimer > 0.75f) {
		circleShot(u, 67.5f);
		u->skillPhase = 4;
	}
}

void Spiral::circleShot(
	Unit *u,
	float angle){

	auto stage = u->stage;

	for (int i = 0; i < 4; ++i){
		auto bullet = new Bullet();
		Vec2 direction = Vec2::UNIT_X.getRotated(
			Vec2::ZERO, DEGREES_TO_RADIANS(angle + 360/4 * i));
		bullet->position = u->position;
		bullet->fire(direction, 600.f);

		bullet->attackData.user = u;
		bullet->attackData.radius = 10;
		bullet->attackData.damage = u->_ATTR(attack);
		bullet->range = u->_ATTR(range);
		bullet->ally = u->ally;

		stage->addUnit(bullet);
	}
}
