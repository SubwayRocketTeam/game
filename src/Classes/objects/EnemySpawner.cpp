#include "pch.h"
#include "EnemySpawner.h"

#include "common/resource.h"

#include "EnemyPool.h"
#include "Enemy.h"
#include "Stage.h"
#include "Ally.h"

using namespace cocos2d;

EnemySpawner::EnemySpawner(){
}
EnemySpawner::~EnemySpawner(){
}

EnemySpawner *EnemySpawner::create(){
	EnemySpawner *e = new EnemySpawner();

	if(e && e->init()){
		e->autorelease();
		return e;
	}
	CC_SAFE_DELETE(e);
	return nullptr;
}
bool EnemySpawner::init(){
	if(!Unit::init(R::EnemySpawner))
		return false;

	scheduleUpdate();

	return true;
}
void EnemySpawner::update(
	float dt){
}

void EnemySpawner::spawn(){
	auto stage = Stage::getInstance(0);
	auto ally = Ally::getInstance(
		Ally::Type::allyEnemy);

	Enemy *e = Enemy::create();
	e->setPosition(
		getPosition());
	e->resetAggro();

	ally->push(e);
	stage->addChild(e);
}