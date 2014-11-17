#pragma once

#include "Unit.h"

#include <map>

#include "common/max.h"

class Enemy : public Unit{
public:
	static Enemy *create();

	void resetAggro();

protected:
	Enemy();
	virtual ~Enemy();

	virtual bool init();
	virtual bool initPhysics();

	virtual void update(
		float dt);

	virtual void onDamage(
		const AttackData &attackData);

	void increaseAggro(
		Unit *u, float value);
	void decreaseAggro(
		Unit *u, float value);
	Unit *getTarget();

protected:
	std::map<Unit*,float> aggros;
};
