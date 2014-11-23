#include "pch.h"
#include "TrashTank.h"

#include "objects/GlobalResource.h"

#include "common/resource.h"

using namespace cocos2d;

static TrashTank *instance = nullptr;

TrashTank *TrashTank::create(){
	instance = new TrashTank();

	if(instance && instance->init()){
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return nullptr;
}
TrashTank *TrashTank::getInstance(){
	return instance;
}

bool TrashTank::init(){
	if(!Sprite::initWithFile(R::TankFrame))
		return false;

	gauge = ProgressTimer::create(
		Sprite::create(R::TankGauge));
	gauge->setType(ProgressTimer::Type::BAR);
	gauge->setOpacity(255);
	gauge->setPercentage(0);
	gauge->setBarChangeRate(Vec2(1,0));
	gauge->setAnchorPoint(Vec2(0,0));
	gauge->setMidpoint(Vec2(0,0));
	addChild(gauge);

	scheduleUpdate();

	return true;
}
void TrashTank::update(
	float dt){

	auto resource = GlobalResource::getInstance();

	gauge->setPercentage(
		(float)resource->trash / Max::Tank * 100.0f);
}