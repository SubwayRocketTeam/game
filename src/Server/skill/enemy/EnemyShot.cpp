#include "stdafx.h"
#include "EnemyShot.h"

#include "Unit.h"
#include "Ally.h"
#include "Bullet.h"
#include "Stage.h"

#include "common/resource.h"

void EnemyShot::use(
	Unit *u,
	Vec2 pos){

	auto stage = u->stage;

	auto bullet = new Bullet();
	bullet->position = u->position;
	bullet->fire(pos - u->position, 600.f);

	bullet->attackData.user = u;
	bullet->attackData.radius = 10;
	bullet->attackData.damage = 1;
	bullet->ally = u->ally;

	stage->addUnit(bullet);
}