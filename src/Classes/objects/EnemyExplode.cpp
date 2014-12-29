#include "pch.h"
#include "EnemyExplode.h"
#include "EnemyType.h"

#include "skill/id.h"

using namespace cocos2d;

EnemyExplode::EnemyExplode(){
	allyID = Ally::Type::allyEnemy;
	skill = nullptr;
	cooltime = 0;
}
EnemyExplode::~EnemyExplode(){
}

EnemyExplode *EnemyExplode::create(
	int stage){
	EnemyExplode *e = new EnemyExplode();

	if (e && e->init(stage)){
		e->autorelease();
		return e;
	}
	CC_SAFE_DELETE(e);
	return nullptr;
}
bool EnemyExplode::init(
	int stage){
	if (!Enemy::init(stage, enemyExplode))
		return false;

	return true;
}

bool EnemyExplode::onDeath(){
	if (!Enemy::onDeath())
		return false;
	useSkill(skillExplosion, getPosition());
	return true;
}