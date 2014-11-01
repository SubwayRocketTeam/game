#include "pch.h"
#include "EnemySpawner.h"

#include "common/resource.h"

#include "EnemyPool.h"
#include "Enemy.h"

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

    return true;
}

void EnemySpawner::spawn(){
	auto pool = EnemyPool::getInstance();

	Enemy *e = Enemy::create();
	e->setPosition(
		getPosition());

	pool->push(e);
}