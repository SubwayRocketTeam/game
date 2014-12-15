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

void Spiral::circleShot(
	Unit* sender,
	Unit *u,
	float angle){

	auto stage = u->stage;

	for (int i = 0; i < 4; ++i){
		auto bullet = new Bullet();
		Vec2 direction = Vec2::UNIT_X.getRotated(
			Vec2::ZERO, DEGREES_TO_RADIANS(angle + 360/4 * i));
		bullet->position = u->position;
		bullet->fire(direction, 1.f);

		bullet->attackData.user = u;
		bullet->attackData.radius = 10;
		bullet->attackData.damage = 1;
		bullet->ally = u->ally;

		stage->addUnit(bullet);
	}
}
