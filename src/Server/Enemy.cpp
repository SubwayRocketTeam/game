#include "stdafx.h"
#include "Enemy.h"

#include "Player.h"
#include "Ally.h"
#include "TrashPool.h"

#include "Stage.h"
#include "GameRoom.h"
#include "CollisionDetector.h"

#include "shared/skill/ActiveSkill.h"

#include "EnemyInfo.h"
#include "EnemyType.h"

#include "PacketType.h"

Enemy::Enemy() :enemyType(0) {
	type = UT_ENEMY;
	ally = Ally::Type::allyEnemy;
	skill = nullptr;
	cooltime = 0;
	followTimer = 0;
	init();
}
Enemy::~Enemy(){
}

bool Enemy::init(){
	if (!Unit::init())
		return false;

	attackData.user = this;
	attackData.object = this;
	attackData.target = nullptr;
	attackData.radius = 30;
	attackData.aggro = 0;
	attackData.damage = 1;

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
	radius = 30;
	return true;
}

void Enemy::update(float dt){

	followTimer -= dt;
	if (followTimer <= 0) {
		updateMovement();
		// TODO: Targt update하는 주기 상수
		followTimer = 0.2f;
	}

	auto target = getTarget();

	attackData.position = position;
	stage->ally[_OPPOSITE(ally)]->processAttack(attackData);

	if (skill)
	{
		if (target && cooltime <= 0.f)
		{
			useSkill(skill->id, target->position);
			// skill->use(this, target->position);
			cooltime = skill->cooltime;
		}
		else
			cooltime -= dt;
	}

	Unit::update(dt);
}

void Enemy::updateMovement(){
	auto target = getTarget();
	if (!target) {
		if (velocity.getLengthSq() != 0.f)
			return;
		velocity = Vec2::ZERO;
	}
	else {
		auto delta = target->position - position;
		velocity = delta.getNormalized() * _ATTR(speed);
	}

	MoveNoti noti;
	noti.id = id;
	noti.start_x = position.x;
	noti.start_y = position.y;
	noti.velocity_x = velocity.x;
	noti.velocity_y = velocity.y;
	stage->gameroom->sendPacket(noti);
}

bool Enemy::onDamage(
	const AttackData &attackData){ ///< attackData요놈은 파라미터 이름이랑 Enemy의 멤버 이름이랑 같다.. 전에 이야기 했던 것 같은데..

	increaseAggro(
		attackData.user, attackData.aggro);

	Attack noti;
	noti.attacker_id = attackData.user->id;
	noti.target_id = id;
	noti.knockback_x = position.x;
	noti.knockback_y = position.y;
	noti.attack_position_x = attackData.position.x;
	noti.attack_position_y = attackData.position.y;
	noti.damage = attackData.damage;
	noti.aggro = attackData.aggro;

	stage->gameroom->sendPacket(noti);
	return true;
}

bool Enemy::onDeath(){
	stage->trashPool->spawn(
		position, (int)_ATTR(drops));

	RemoveUnit noti;
	noti.id = id;
	stage->gameroom->sendPacket(noti);

	return true;
}

void Enemy::resetAggro(){
	auto players = stage->ally[Ally::Type::allyPlayer];
	auto pos = position;

	for (auto player : *players){
		auto playerPos = player->position;

		aggros[player] = pos.getDistance(playerPos);
	}

	updateMovement();
}
void Enemy::increaseAggro(
	Unit *u, float value){

	// _ASSERT(aggros.find(u) != aggros.end());
	if (aggros.find(u) != aggros.end())
		aggros[u] += value;
}
void Enemy::decreaseAggro(
	Unit *u, float value){

	// _ASSERT(aggros.find(u) != aggros.end());

	if (aggros.find(u) != aggros.end())
		aggros[u] -= value;
}
void Enemy::removeAggro(
	Unit* u) {
	// _ASSERT(aggros.find(u) != aggros.end());
	if (aggros.find(u) != aggros.end())
		aggros.erase(u);
}

Unit *Enemy::getTarget(){

	if (aggros.empty())
		return nullptr;

	Unit *target = aggros.begin()->first;
	float max = aggros.begin()->second;

	for (auto pair : aggros){
		if (pair.second > max){
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

void Enemy::setInfo(EnemyInfo* info, int enemy_type) {
	enemyType = enemy_type;

	std::map<std::string, Attribute>::iterator it = info->attrs.begin();
	for (; it != info->attrs.end(); it++) {
		attrs[it->first] = it->second;
	}

	radius = _ATTR(radius);
	attackData.damage = _ATTR(melee_attack);
	_INIT_ATTR(drops, info->cost * 2);

	if (info->skills.size() > 0)
		skill = info->skills[0];
}