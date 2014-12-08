#include "pch.h"
#include "Enemy_Explode.h"

#include "skill/id.h"

using namespace cocos2d;

Enemy_Explode::Enemy_Explode(){
	allyID = Ally::Type::allyEnemy;
	skill = nullptr;
	cooltime = 0;
}
Enemy_Explode::~Enemy_Explode(){
}

Enemy_Explode *Enemy_Explode::create(){
	Enemy_Explode *e = new Enemy_Explode();

	if (e && e->init()){
		e->autorelease();
		return e;
	}
	CC_SAFE_DELETE(e);
	return nullptr;
}
bool Enemy_Explode::init(){
	if (!Enemy::init())
		return false;

	return true;
}

bool Enemy_Explode::onDeath(){
	if (!Enemy::onDeath())
		return false;
	useSkill(skillExplosion, getPosition());
	return true;
}