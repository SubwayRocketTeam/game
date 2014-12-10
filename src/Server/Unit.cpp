#include "stdafx.h"
#include "Unit.h"

#include "Stage.h"
#include "CollisionDetector.h"

#include "AttackData.h"

#include "shared/skill/SkillPool.h"
#include "shared/skill/ActiveSkill.h"
#include "shared/skill/PassiveSkill.h"

struct Unit::PassiveData{
	float remaining;
	float update;
	float interval;
};

Unit::Unit()
	:stage(nullptr)
	, id(INVALID_ID), type(UT_NONE), ally(0)
	, friction(0), radius(0) {
}
Unit::~Unit(){
}

bool Unit::init(){
	if (!initPhysics())
		return false;
	if (!initAttrs())
		return false;
	return true;
}

bool Unit::initAttrs(){
	_INIT_ATTR(hp, 3);
	_INIT_ATTR(mp, 0);
	_INIT_ATTR(speed, 8);
	_INIT_ATTR(hpRegen, 0.0f);
	_INIT_ATTR(mpRegen, 0.0f);
	_INIT_ATTR(defence, 0.0f);
	_INIT_ATTR(range, 120);
	_INIT_ATTR(attack, 50);

	return true;
}

bool Unit::initPhysics(){
	return true;
}

void Unit::update(float dt) {
	updateGen(dt);
	updatePassives(dt);
	updatePhysics(dt);
}

void Unit::updateGen(float dt){
	__ATTR(hp).increase(_ATTR(hpRegen) * dt);
	__ATTR(mp).increase(_ATTR(mpRegen) * dt);
}
void Unit::updatePassives(float dt){

	std::vector<int> removeList;

	for (auto &pair : passives){
		auto id = pair.first;
		auto &data = pair.second;
		auto skill = SkillPool::getInstance()->get(id);

		data.remaining -= dt;
		data.update -= dt;

		/* 지속 시간이 끝났으면 지우기 */
		if (skill->duration != Skill::Infinite &&
			data.remaining <= 0)
			removeList.push_back(id);
		/* interval마다 update 호출해주기 */
		else if (data.interval != 0){
			if (data.update <= 0){
				auto pool = SkillPool::getInstance();
				auto skill = (PassiveSkill*)pool->get(id);

				if (!skill->update(this, data.remaining))
					removeList.push_back(id);

				data.update = data.interval;
			}
		}
	}

	for (auto id : removeList)
		removePassive(id);
}

void Unit::updatePhysics(float dt){
	velocity += acceleration * dt;
	velocity = velocity.getNormalized() * max(0, velocity.getLength() - friction * dt);
	position += velocity * dt;
}

bool Unit::onDamage(const AttackData &attackData){
	return true;
}

bool Unit::onDeath(){
	return true;
}

bool Unit::damage(const AttackData& attackData){
	if (onDamage(attackData)){
		__ATTR(hp).increase(-max(0, attackData.damage - _ATTR(defence)));
	}

	if (_ATTR(hp) <= 0) {
		if (onDeath()){
			stage->removeUnit(this);
			return true;
		}
	}
	return false;
}

bool Unit::useSkill(int id,	Vec2 pos){

	auto pool = SkillPool::getInstance();
	auto skill = (ActiveSkill*)pool->get(id);

	if (skill)
		skill->use(this, pos);

	return true;
}
void Unit::addPassive(int id){

	auto pool = SkillPool::getInstance();
	auto skill = (PassiveSkill*)pool->get(id);

	/* 이미 가지고 있는 패시브 */
	if (passives.find(id) != passives.end())
		return;

	/* TODO : 패시브 중복 적용이면
	남은 시간 더하기 or 초기화할건지 */
	PassiveData data;
	data.update = data.interval = skill->interval;
	data.remaining = skill->duration;
	passives[id] = data;

	for (auto pair : skill->bonusList){
		std::string name = pair.first;
		Attribute attr = pair.second;
		Attribute &target = attrs[name];

		target.getBonusValue() += attr.getBonusValue();
		target.getBonusRate() += attr.getBonusRate();
	}
}

void Unit::removePassive(int id){

	auto pool = SkillPool::getInstance();
	auto skill = (PassiveSkill*)pool->get(id);

	_ASSERT(passives.find(id) != passives.end());

	passives.erase(id);

	for (auto pair : skill->bonusList){
		std::string name = pair.first;
		Attribute attr = pair.second;
		Attribute &target = attrs[name];

		target.getBonusValue() -= attr.getBonusValue();
		target.getBonusRate() -= attr.getBonusRate();
	}
}

Attribute &Unit::getAttribute(const std::string &name){

	_ASSERT(attrs.find(name) != attrs.end());

	return attrs[name];
}

void Unit::collide(Vec2 delta, Unit* other){
	position += delta * 0.5f;
}
