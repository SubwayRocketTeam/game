#include "pch.h"
#include "Enemy.h"

#include "common/resource.h"
#include "common/PhysicsFactory.h"

#include "Player.h"
#include "Ally.h"
#include "TrashPool.h"

#include "Stage.h"
#include "CollisionDetector.h"

#include "skill/ActiveSkill.h"

#include "objects/EnemyInfo.h"

using namespace cocos2d;

Enemy::Enemy(){
	allyID = Ally::Type::allyEnemy;
	skill = nullptr;
	cooltime = 0;
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

	attackData.user = this;
	attackData.object = this;
	attackData.target = nullptr;
	attackData.radius = 30;
	attackData.type = AttackType::Pan;
	attackData.aggro = 0;
	attackData.damage = 1;

	scheduleUpdate();

	return true;
}

bool Enemy::initAttrs(){
	if (!Unit::initAttrs())
		return false;

	_INIT_ATTR(speed, 50);
	_INIT_ATTR(drops, 10);

	return true;
}


bool Enemy::initPhysics(){
	Stage::getInstance(0)->getCollisionDetector()->addUnit(this);
	radius = 30;
	return true;
	/*
	auto factory = PhysicsFactory::getInstance();
	auto pbody = factory->make("enemy");

	if(pbody){
		pbody->setAngularDamping(100000000);
		setPhysicsBody(pbody);
		return true;
	}
	return true;
	*/
}

void Enemy::update(
	float dt){

	auto target = getTarget();

	auto delta = getPosition() - target->getPosition();
	
	auto move = delta.getNormalized() * _ATTR(speed);
	auto angle = 
		CC_RADIANS_TO_DEGREES(delta.getAngle(getPosition()));

//	getPhysicsBody()->setVelocity(-move);

	attackData.postion = getPosition();
	Ally::getInstance(_OPPOSITE(allyID))->processAttack(attackData);

	if (skill)
	{
		if (cooltime <= 0.f)
		{
			skill->use(this, target->getPosition());
			cooltime = skill->cooltime;
			cooltime *= _ATTR(attackSpeed);
		}
		else
			cooltime -= dt;
	}
}

bool Enemy::onDamage(
	const AttackData &attackData){

	increaseAggro(
		attackData.user, attackData.aggro);

	return true;
}

bool Enemy::onDeath(){
	TrashPool::getInstance()->spawn(
		getPosition(), _ATTR(drops));

	return true;
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

void Enemy::setSkill(
	ActiveSkill* skill){
	this->skill = skill;
}
ActiveSkill* Enemy::getSkill(){
	return skill;
}

void Enemy::setInfo(EnemyInfo* info) {
	std::map<std::string, Attribute>::iterator it = info->attrs.begin();
	for (; it != info->attrs.end(); it++) {
		attrs[it->first] = it->second;
	}

	skill = info->skills[0];
}