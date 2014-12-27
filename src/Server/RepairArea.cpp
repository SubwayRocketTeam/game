#include "stdafx.h"
#include "RepairArea.h"

#include "Stage.h"
#include "GameRoom.h"
#include "Ally.h"

#include "PacketType.h"

#include "common/resource.h"
#include "config.h"

#include "shared/skill/id.h"


RepairArea::RepairArea(Stage* const stage)
	:stage(stage) {
}
RepairArea::~RepairArea(){
}

bool RepairArea::init(){
	if (!Unit::init())
		return false;

	// 위치 선정
	position = Vec2(200, 200);

	// 전송
	SpawnUnit noti;
	noti.id = id;
	noti.stage = stage->id;
	noti.unit_type = UNIT_REPAIR_AREA;
	noti.x = position.x;
	noti.y = position.y;
	stage->gameroom->sendPacket(noti);


	return true;
}

void RepairArea::update(
	float dt){

	auto players = stage->ally[Ally::Type::allyPlayer];

	for (auto player : *players){
		Vec2 pos = player->position;

		if (std::abs(pos.x - position.x) < config::repair_area_size
			&& std::abs(pos.y - position.y) < config::repair_area_size)
			player->addPassive(skillRepair);
	}
}