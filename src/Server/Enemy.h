#pragma once

#include "Unit.h"
#include "AttackData.h"

class ActiveSkill;
struct EnemyInfo;

class Enemy : public Unit{
public:
	Enemy();
	virtual ~Enemy();

	virtual bool init();
	virtual bool initAttrs();
	virtual bool initPhysics();

	void resetAggro();

	void setSkill(ActiveSkill* skill);
	ActiveSkill* getSkill();

	void setInfo(EnemyInfo* info, int enemy_type);

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

	int getEnemyType() const;

protected:
	int enemyType;

	std::map<Unit*, float> aggros;
	AttackData attackData;

	ActiveSkill* skill;
	float cooltime;
};
