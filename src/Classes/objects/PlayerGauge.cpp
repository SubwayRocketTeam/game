#include "pch.h"
#include "PlayerGauge.h"
#include "Player.h"

#include "common/resource.h"

using namespace cocos2d;

float const PlayerGauge::FadeDuration = 0.2;

PlayerGauge::PlayerGauge() :
	hp(0), hpMax(0){
}
PlayerGauge::~PlayerGauge(){
}

PlayerGauge *PlayerGauge::create(
	float hp, float hpMax){

	PlayerGauge *p = new PlayerGauge;
	
	if(p && p->init(hp, hpMax)){
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool PlayerGauge::init(
	float _hp, float _hpMax){

	if(!ProgressTimer::initWithSprite(Sprite::create(R::PlayerGauge)))
		return false;

	hp = _hp;
	hpMax = _hpMax;

	setType(ProgressTimer::Type::RADIAL);
	setPercentage(100.0f);
	setScaleX(-1); /* 시계 방향을 위해 */

	scheduleUpdate();

	return true;
}
void PlayerGauge::update(
	float dt){

	Player *player = (Player*)getParent();

	if( hp != player->_ATTR(hp) ||
		hpMax != player->_ATTR_MAX(hp)){

		hp = player->_ATTR(hp);
		hpMax = player->_ATTR_MAX(hp);

		/* TODO : 체력 줄어들 때도 에니메이션? */
		/*
		runAction(
			ProgressTo::create(
				FadeDuration, hp/hpMax*100.0f))
		*/
		setPercentage(hp/hpMax*100.0f);
	}

	this->setRotation(-player->getRotation());
}