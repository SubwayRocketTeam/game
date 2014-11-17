#include "pch.h"
#include "Enemy.h"
#include "PartedBody.h"

#include "common/resource.h"
#include "common/PhysicsFactory.h"
#include "common/World.h"

#include "Player.h"
#include "Ally.h"

using namespace cocos2d;

Enemy::Enemy(){
	allyID = Ally::Type::allyEnemy;
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
	auto factory = World::getInstance();
	auto pbody = factory->make(this);

	if(pbody) {
		_pBody = pbody;
		return true;
	}

	return true;
}

void Enemy::update(
	float dt){

	auto target = getTarget();

	auto delta = getPosition() - target->getPosition();
	
	auto move = delta / PTM_RATIO;
	move = move.getNormalized();
	auto angle = 
		CC_RADIANS_TO_DEGREES(delta.getAngle(getPosition()));

	body->setRotation(angle+90);
	b2Vec2 velocity = b2Vec2(move.x, move.y);
	_pBody->SetLinearVelocity(-velocity);

	this->setPosition(
		Vec2(_pBody->GetPosition().x * PTM_RATIO,
		_pBody->GetPosition().y * PTM_RATIO));

	if(rand() % 40 == 1)
		useSkill(10,getPosition().x, getPosition().y);
}

void Enemy::focus(){
	body->setColor(Color3B(255,0,0));
}
void Enemy::unfocus(){
	body->setColor(Color3B(255,255,255));
}

void Enemy::onDamage(
	const AttackData &attackData){

	increaseAggro(
		attackData.user, attackData.aggro);
}

void Enemy::resetAggro(){
	auto players = Ally::getInstance(
		Ally::Type::allyPlayer);
	auto pos = getPosition();

	for(auto player : *players){
		auto playerPos = player->getPosition();

		aggros[player] = pos.getDistance(playerPos);
	}
}
void Enemy::increaseAggro(
	Unit *u, float value){

	CC_ASSERT(aggros.find(u) != aggros.end());
	
	aggros[u] += value;
}
void Enemy::decreaseAggro(
	Unit *u, float value){

	CC_ASSERT(aggros.find(u) != aggros.end());

	aggros[u] -= value;
}
Unit *Enemy::getTarget(){
	Unit *target = nullptr;
	float max = 0;

	for(auto pair : aggros){
		if(pair.second > max){
			target = pair.first;
			max = pair.second;
		}
	}

	return target;
}