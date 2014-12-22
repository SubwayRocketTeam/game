#include "stdafx.h"
#include "Slash.h"

#include "Unit.h"
#include "Bullet.h"
#include "Stage.h"

void Slash::use(
	Unit *u,
	Vec2 pos){

	auto stage = u->stage;

	auto bullet = new Bullet();
	bullet->position = u->position;
	bullet->fire(pos - u->position, 800);

	bullet->attackData.user = u;
	bullet->attackData.radius = 10;
	bullet->attackData.damage = 1;
	bullet->ally = u->ally;

	stage->addUnit(bullet);
}