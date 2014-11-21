#include "pch.h"
#include "PlayerGauge.h"
#include "Player.h"

#include "common/resource.h"

using namespace cocos2d;

PlayerGauge *PlayerGauge::create(){
	PlayerGauge *p = new PlayerGauge;
	
	if(p && p->init()){
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool PlayerGauge::init(){
	if(!ProgressTimer::initWithSprite(Sprite::create(R::PlayerGauge)))
		return false;

	setType(ProgressTimer::Type::RADIAL);
	setPercentage(100.0f);

	scheduleUpdate();

	return true;
}
void PlayerGauge::update(
	float dt){

	Player *player = (Player*)getParent();

	float hp = player->_ATTR(hp);
	float max = player->_ATTR_MAX(hp);

	setPercentage(hp/max*100.0f);
}