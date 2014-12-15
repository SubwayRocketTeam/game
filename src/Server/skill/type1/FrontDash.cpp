#include "stdafx.h"
#include "FrontDash.h"

#include "Unit.h"

#include "common/resource.h"

bool FrontDash::initExternalData(
	const std::string &dstPath){

	if(!ActiveSkill::initExternalData(dstPath))
		return false;
	
	distance = json.get("distance", 0).asFloat();

	return true;
}

void FrontDash::use(
	Unit *u,
	Vec2 pos){

	/*
	Vec2 angle = u->direction;
	u->runAction(
		MoveBy::create(duration, foward * distance));
	*/
}

void FrontDash::update(
	Unit* u,
	float dt) {
	u->position += u->direction * 10.f * dt;
}