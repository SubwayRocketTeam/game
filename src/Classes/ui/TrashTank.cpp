#include "pch.h"
#include "TrashTank.h"

#include "objects/GlobalResource.h"

#include "common/resource.h"

using namespace cocos2d;

static TrashTank *instance = nullptr;

TrashTank::TrashTank() :
	gauge(nullptr), overlay(nullptr),
	cost(0){
}
TrashTank::~TrashTank(){
}

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

	BlendFunc blend;
	blend.src = GL_ONE;
	blend.dst = GL_SRC_ALPHA;

	overlay = Sprite::create(R::TankGauge);
	overlay->setAnchorPoint(Vec2(0,0));
	overlay->setBlendFunc(blend);
	overlay->setVisible(false);
	addChild(overlay);

	scheduleUpdate();

	return true;
}
void TrashTank::update(
	float dt){

	auto resource = GlobalResource::getInstance();
	gauge->setPercentage(
		(float)resource->trash / Max::Tank * 100.0f);

	/* 블링크 영역 업데이트 */
	auto size = gauge->getContentSize();
	float x =
		MAX(0, size.width * ((resource->trash-cost) / Max::Tank));
	float width = 
		size.width * MIN((float)resource->trash / Max::Tank, cost / Max::Tank);
	overlay->setTextureRect(
		Rect(x,0, width,size.height));
	overlay->setPositionX(x);
}

void TrashTank::blink(
	float _cost){
		
	cost = _cost;
	overlay->setOpacity(255);
	overlay->setVisible(true);
	overlay->runAction(
		RepeatForever::create(
		Sequence::create(
			FadeTo::create(0.3, 128),
			FadeTo::create(0.3, 200),
			nullptr
		)));
}
void TrashTank::stopBlink(){
	overlay->setVisible(false);
	overlay->stopAllActions();
}

float TrashTank::getCostX(
	float _cost) {
	auto size = gauge->getContentSize();
	return MAX(0, size.width * _cost / Max::Tank);
}

