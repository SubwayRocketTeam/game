#include "EnemySpawner.h"

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
    if(!Unit::init())
		return false;

    return true;
}

void EnemySpawner::spawn(){
	auto pool = EnemyPool::getInstance();

	for(int i=0;i<20;i++){
		Enemy *e = Enemy::create();

		e->setPosition(Vec2(rand()%800, rand()%600));

		pool->push(e);
	}
}