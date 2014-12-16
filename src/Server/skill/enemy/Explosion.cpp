#include "stdafx.h"
#include "Explosion.h"

#include "Unit.h"
#include "Ally.h"
#include "Bullet.h"
#include "Stage.h"

#include "common/resource.h"

void Explosion::use(
	Unit *u,
	Vec2 pos){
	circleShot(nullptr, u, DEGREES_TO_RADIANS(rand() % 360));
}

void Explosion::circleShot(
	Unit* sender,
	Unit *u,
	float angle){

	auto stage = u->stage;

	for (int i = 0; i < 32; ++i){
		auto bullet = new Bullet();
		Vec2 direction = Vec2::UNIT_X.getRotated(
			Vec2::ZERO, DEGREES_TO_RADIANS(angle + 360/32 * i));
		bullet->position = u->position;
		bullet->fire(direction, 1200.f);

		bullet->attackData.user = u;
		bullet->attackData.radius = 10;
		bullet->attackData.damage = 1;
		bullet->ally = u->ally;

		stage->addUnit(bullet);
	}
}
