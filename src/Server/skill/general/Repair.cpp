#include "stdafx.h"
#include "Repair.h"

#include "Unit.h"
#include "Stage.h"
#include "RepairArea.h"

#include "config.h"

bool Repair::update(
	Unit *user,
	float remaining){

	auto stage = user->stage;
	auto repairArea = stage->repairArea;
	auto delta = repairArea->position - user->position;

	if(std::abs(delta.x) < config::repair_area_size
		&& std::abs(delta.y) < config::repair_area_size)
		return true;
	return false;
}