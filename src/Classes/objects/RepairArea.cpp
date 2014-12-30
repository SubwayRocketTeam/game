#include "pch.h"
#include "RepairArea.h"

#include "common/resource.h"

#include "skill/id.h"

#include "Ally.h"
#include "tags.h"

using namespace cocos2d;

/* TODO : json에서 리젠률 설정 */
RepairArea::RepairArea(){
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

	return true;
}