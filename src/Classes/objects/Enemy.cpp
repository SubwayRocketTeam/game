#include "pch.h"
#include "Enemy.h"
#include "PartedBody.h"

#include "common/resource.h"
#include "common/PhysicsFactory.h"

#include "Player.h"

using namespace cocos2d;

Enemy::Enemy(){
}
Enemy::~Enemy(){
}

Enemy *Enemy::create(){
	Enemy *e = new Enemy();

	if(e && e->init()){
		e->autorelease();
		return e;
	}
	CC_SAFE_DELETE(e);
	return nullptr;
}
bool Enemy::init(){
	if (!Unit::init(R::EnemyBody))
		return false;

	scheduleUpdate();

	return true;
}
bool Enemy::initPhysics(){
	auto factory = PhysicsFactory::getInstance();
	auto pbody = factory->make("enemy");

	if(pbody){
		setPhysicsBody(pbody);
		return true;
	}

	return true;
}

void Enemy::update(
	float dt){

	auto player = Player::getInstance();
	auto delta = getPosition() - player->getPosition();

	auto move = delta.getNormalized() * 50;
	
	getPhysicsBody()->setVelocity(-move);
}

void Enemy::focus(){
	body->setColor(Color3B(255,0,0));
}
void Enemy::unfocus(){
	body->setColor(Color3B(255,255,255));
}