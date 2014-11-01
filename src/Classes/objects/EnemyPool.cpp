#include "pch.h"
#include "EnemyPool.h"

#include "Enemy.h"

using namespace cocos2d;

static EnemyPool *pool = nullptr;

EnemyPool::EnemyPool(){
}
EnemyPool::~EnemyPool(){
}

EnemyPool *EnemyPool::create(){
	pool = new EnemyPool();

	if(pool && pool->init()){
		pool->autorelease();
		return pool;
	}
	CC_SAFE_DELETE(pool);
	return nullptr;
}
EnemyPool *EnemyPool::getInstance(){
	return pool;
}

bool EnemyPool::init(){
    
    return true;
}

void EnemyPool::push(
	Enemy *e){

	addChild(e);
}
void EnemyPool::remove(
	Enemy *e){

	removeChild(e);
}

void EnemyPool::focus(
	Enemy *e){

	auto enemies = getChildren();
	for(auto enemy : enemies){
		((Enemy*)enemy)->unfocus();
	}
	if(e != nullptr)
		e->focus();
}