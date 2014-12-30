#include "pch.h"
#include "RepairArea.h"

#include "common/resource.h"

#include "tags.h"

using namespace cocos2d;

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