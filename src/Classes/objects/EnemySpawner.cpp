#include "pch.h"
#include "EnemySpawner.h"
#include "EnemyFactory.h"

#include "common/resource.h"

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

	/*
	if(rand()%1000 == 1){
		spawn(enemySpiral);
	}
	*/
}
 
void EnemySpawner::spawn(
	EnemyType type){

	auto stage = Stage::getInstance(0);
	auto ally = Ally::getInstance(
		Ally::Type::allyEnemy);
	auto factory = EnemyFactory::getInstance();

	Enemy *e = factory->createEnemy(type);
	e->setPosition(
		getPosition());
	e->resetAggro();

	ally->push(e);
	stage->addChild(e, Z::unit);
}