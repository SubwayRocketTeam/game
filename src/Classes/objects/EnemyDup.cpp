#include "pch.h"
#include "EnemyDup.h"

#include "skill/id.h"

using namespace cocos2d;

EnemyDup::EnemyDup(){
	allyID = Ally::Type::allyEnemy;
	skill = nullptr;
	cooltime = 0;
}
EnemyDup::~EnemyDup(){
}

EnemyDup *EnemyDup::create(){
	EnemyDup *e = new EnemyDup();

	if (e && e->init()){
		e->autorelease();
		return e;
	}
	CC_SAFE_DELETE(e);
	return nullptr;
}
bool EnemyDup::init(){
	if (!Enemy::init())
		return false;

	return true;
}

bool EnemyDup::onDeath(){
	if (!Enemy::onDeath())
		return false;

	useSkill(skillExplosion, getPosition());

	return true;
}