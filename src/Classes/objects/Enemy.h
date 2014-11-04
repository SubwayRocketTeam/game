#pragma once

#include "Unit.h"

#include <map>

#include "common/max.h"

class Enemy : public Unit{
public:
	static Enemy *create();
	
    virtual bool init();

	void focus();
	void unfocus();

	void resetAggro();

protected:
	Enemy();
	virtual ~Enemy();

	virtual bool initPhysics();

	virtual void update(
		float dt);

protected:
	std::map<Unit*,float> aggros;
};
