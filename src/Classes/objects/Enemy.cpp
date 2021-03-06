﻿#include "pch.h"
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

Enemy *Enemy::create(
	int stage,
	int enemyType){
	Enemy *e = new Enemy();

	if(e && e->init(stage, enemyType)){
		e->autorelease();
		return e;
	}
	CC_SAFE_DELETE(e);
	return nullptr;
}
bool Enemy::init(
	int stage,
	int enemyType){

	stageID = stage;
	
	if (!Unit::init(_MAKE_PATH("enemy%d", enemyType+1)))
		return false;


	/*
	enemyAttackData.user = this;
	enemyAttackData.object = this;
	enemyAttackData.target = nullptr;
	enemyAttackData.radius = 30;
	enemyAttackData.aggro = 0;
	enemyAttackData.damage = 1;
	*/

	runAction(
		RepeatForever::create(
		RotateBy::create(0.5f, 180)
		));

	scheduleUpdate();

	return true;
}

bool Enemy::initAttrs(){
	if (!Unit::initAttrs())
		return false;

	_INIT_ATTR(speed, 5);
	_INIT_ATTR(drops, 10);

	return true;
}


bool Enemy::initPhysics(){
	Stage::getInstance(stageID)->getCollisionDetector()
		->addUnit(this);
	// radius = 30;

	return true;
}

void Enemy::update(
	float dt){

	// 이동, 공격, 스킬 전부 다 서버에서 처리
	/*
	auto target = getTarget();
	auto speed = _ATTR(speed);

	if(speed && target){
		auto delta = getPosition() - target->getPosition();
		auto move = delta.getNormalized() * speed;
		auto angle = 
			CC_RADIANS_TO_DEGREES(delta.getAngle(getPosition()));

		runAction(
			MoveBy::create(dt, -move));
	}

	attackData.position = getPosition();
	Stage::getInstance()->getAlly(_OPPOSITE(allyID))->processAttack(attackData);

	if (skill)
	{
		if (cooltime <= 0.f)
		{
			skill->use(this, target->getPosition());
			cooltime = skill->cooltime;
		}
		else
			cooltime -= dt;
	}
	*/
}

bool Enemy::onDamage(
	const AttackData &attackData){

	increaseAggro(
		attackData.user, attackData.aggro);

	return true;
}

bool Enemy::onDeath(){
	/*
	TrashPool::getInstance()->spawn(
		getPosition(), _ATTR(drops));
	*/
	return Unit::onDeath();
}

void Enemy::resetAggro(){
	auto players = Stage::getInstance(stageID)->getAlly(
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
void Enemy::removeAggro(
	Unit* u) {
	CC_ASSERT(aggros.find(u) != aggros.end());
	aggros.erase(u);
}
Unit *Enemy::getTarget(){

	if (aggros.empty())
		return nullptr;

	Unit *target = aggros.begin()->first;
	float max = aggros.begin()->second;

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

	radius = _ATTR(radius);

	if (info->skills.size() > 0)
		skill = info->skills[0];
}