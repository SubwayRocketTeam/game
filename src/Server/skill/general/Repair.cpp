#include "stdafx.h"
#include "Repair.h"

#include "Unit.h"
#include "Stage.h"

bool Repair::update(
	Unit *user,
	float remaining){

	auto stage = user->stage;
	/*
	auto repairArea =
		stage->getChildByTag(UnitType::RepairArea);

	if(repairArea->getBoundingBox().containsPoint(
		user->getPosition()))
		return true;
	*/
	return false;
}