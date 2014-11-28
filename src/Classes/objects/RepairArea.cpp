#include "pch.h"
#include "RepairArea.h"

#include "common/resource.h"

#include "skill/id.h"

#include "Ally.h"
#include "tags.h"

using namespace cocos2d;

/* TODO : json에서 리젠률 설정 */
RepairArea::RepairArea() :
	regen(4){
}
RepairArea::~RepairArea(){
}

RepairArea *RepairArea::create(){
	RepairArea *e = new RepairArea();

	if(e && e->init()){
		e->autorelease();
		return e;
	}
	CC_SAFE_DELETE(e);
	return nullptr;
}
bool RepairArea::init(){
	if (!Unit::init(R::RepairArea))
		return false;

	setTag(UnitType::RepairArea);
	scheduleUpdate();

	return true;
}

void RepairArea::update(
	float dt){

	auto players = Ally::getInstance(
		Ally::Type::allyPlayer);

	Rect rect = getBoundingBox();
	for(auto player : *players){
		Vec2 pos = player->getPosition();

		if(rect.containsPoint(pos))
			player->addPassive(skillRepair);
	}
}