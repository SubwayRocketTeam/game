#include "pch.h"
#include "EnemyDup.h"
#include "EnemyType.h"

#include "skill/id.h"

using namespace cocos2d;

EnemyDup::EnemyDup(){
	allyID = Ally::Type::allyEnemy;
	skill = nullptr;
	cooltime = 0;
}
EnemyDup::~EnemyDup(){
}

EnemyDup *EnemyDup::create(
	int stage){
	EnemyDup *e = new EnemyDup();

	if (e && e->init(stage)){
		e->autorelease();
		return e;
	}
	CC_SAFE_DELETE(e);
	return nullptr;
}
bool EnemyDup::init(
	int stage){
	if (!Enemy::init(stage, enemyDup))
		return false;

	return true;
}

bool EnemyDup::onDeath(){
	if (!Enemy::onDeath())
		return false;

	useSkill(skillExplosion, getPosition());

	return true;
}