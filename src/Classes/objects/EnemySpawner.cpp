#include "pch.h"
#include "EnemySpawner.h"

#include "common/resource.h"

#include "EnemyPool.h"
#include "Enemy.h"
#include "Stage.h"

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

	if(rand()%40 == 1){
		spawn();
	}
}

void EnemySpawner::spawn(){
	auto stage = Stage::getInstance(0);

	Enemy *e = Enemy::create();
	e->setPosition(
		getPosition());

	stage->addChild(e);
}