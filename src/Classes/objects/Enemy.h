#pragma once

#include "Unit.h"

#include <map>

#include "common/max.h"

class ActiveSkill;
struct EnemyInfo;

class Enemy : public Unit{
public:
	static Enemy *create(
		int enemyType);

	void resetAggro();

	void setSkill(
		ActiveSkill* skill);
	ActiveSkill* getSkill();

	void setInfo(EnemyInfo* info);

	void removeAggro(
		Unit* u);

protected:
	Enemy();
	virtual ~Enemy();

	virtual bool init(
		int enemyType);
	virtual bool initAttrs();
	virtual bool initPhysics();

	virtual void update(
		float dt);

	virtual bool onDamage(
		const AttackData &attackData);
	virtual bool onDeath();

	void increaseAggro(
		Unit *u, float value);
	void decreaseAggro(
		Unit *u, float value);
	Unit *getTarget();

protected:
	std::map<Unit*,float> aggros;
	AttackData attackData;

	ActiveSkill* skill;
	float cooltime;

	cocos2d::LabelTTF* label;

	cocos2d::Sprite *shadow;

};
