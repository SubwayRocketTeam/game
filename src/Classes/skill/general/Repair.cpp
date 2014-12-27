#include "pch.h"
#include "Repair.h"

#include "objects/Unit.h"
#include "objects/Stage.h"
#include "objects/tags.h"

using namespace std;
using namespace cocos2d;

bool Repair::update(
	Unit *user,
	float remaining){

	/*
	auto stage = Stage::getInstance(0);
	auto repairArea =
		stage->getChildByTag(UnitType::RepairArea);

	if(repairArea->getBoundingBox().containsPoint(
		user->getPosition()))
		return true;
	return false;
	*/
	return true;
}